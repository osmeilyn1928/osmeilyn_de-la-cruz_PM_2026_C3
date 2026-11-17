#include "costos_core.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *CATEGORIAS[6] = {
    "Combustible", "Mantenimiento", "Reparacion",
    "Seguro", "Impuestos", "Otros"
};

char marca[40] = "";
char modelo[40] = "";
char placa[16] = "";
int anio = 0;
int hay_vehiculo = 0;
long odometro = 0;

struct Gasto gastos[MAX_GASTOS];
int n = 0;
unsigned long siguiente_id = 1;

static void set_error(char *error, size_t error_tam, const char *msg) {
    if (error && error_tam > 0) {
        strncpy(error, msg, error_tam - 1);
        error[error_tam - 1] = '\0';
    }
}

int costos_fecha_ok(const char *f)
{
    int a, m, d;
    int dias_mes[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int i;

    if (f == NULL || strlen(f) != 10) return 0;
    for (i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (f[i] != '-') return 0;
        } else if (!isdigit((unsigned char)f[i])) {
            return 0;
        }
    }
    if (sscanf(f, "%4d-%2d-%2d", &a, &m, &d) != 3) return 0;
    if (a < 1900 || m < 1 || m > 12) return 0;
    if (a % 4 == 0 && (a % 100 != 0 || a % 400 == 0)) dias_mes[1] = 29;
    return d >= 1 && d <= dias_mes[m - 1];
}

static void limitar_utf8(char *s, size_t max_bytes)
{
    size_t len = strlen(s);
    size_t corte;
    if (len <= max_bytes) return;
    corte = max_bytes;
    while (corte > 0 && (((unsigned char)s[corte] & 0xC0U) == 0x80U)) {
        corte--;
    }
    s[corte] = '\0';
}

void costos_limpiar_descripcion(char *s)
{
    size_t i;
    if (!s) return;
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == '|' || s[i] == ';' || s[i] == '\n' || s[i] == '\r') {
            s[i] = ',';
        }
    }
    limitar_utf8(s, MAX_DESC);
}

int costos_guardar(char *error, size_t error_tam)
{
    FILE *f = fopen(ARCHIVO_DATOS, "w");
    int i;
    if (f == NULL) {
        set_error(error, error_tam, "No se pudo guardar el archivo de datos.");
        return 0;
    }
    fprintf(f, "VEHICULO;%s;%s;%s;%d;%ld;%lu\n",
            marca, modelo, placa, anio, odometro, siguiente_id);
    for (i = 0; i < n; i++) {
        fprintf(f, "GASTO;%lu;%s;%d;%.2f;%ld;%.2f;%s\n",
                gastos[i].id, gastos[i].fecha, gastos[i].cat,
                gastos[i].monto, gastos[i].km, gastos[i].litros, gastos[i].desc);
    }
    if (fclose(f) != 0) {
        set_error(error, error_tam, "Hubo un problema al cerrar el archivo de datos.");
        return 0;
    }
    return 1;
}

void costos_cargar(void)
{
    FILE *f = fopen(ARCHIVO_DATOS, "r");
    char linea[512];
    int i;
    if (f == NULL) return;

    while (fgets(linea, sizeof linea, f) != NULL) {
        linea[strcspn(linea, "\r\n")] = '\0';
        if (strncmp(linea, "VEHICULO;", 9) == 0) {
            char marca_tmp[40] = "", modelo_tmp[40] = "", placa_tmp[16] = "";
            int anio_tmp = 0; long odometro_tmp = 0; unsigned long prox = 1;
            if (sscanf(linea + 9, "%39[^;];%39[^;];%15[^;];%d;%ld;%lu",
                       marca_tmp, modelo_tmp, placa_tmp, &anio_tmp, &odometro_tmp, &prox) >= 5) {
                strncpy(marca, marca_tmp, sizeof marca - 1); marca[sizeof marca - 1] = '\0';
                strncpy(modelo, modelo_tmp, sizeof modelo - 1); modelo[sizeof modelo - 1] = '\0';
                strncpy(placa, placa_tmp, sizeof placa - 1); placa[sizeof placa - 1] = '\0';
                anio = anio_tmp; odometro = odometro_tmp; hay_vehiculo = 1;
                if (prox > 0) siguiente_id = prox;
            }
        } else if (strncmp(linea, "GASTO;", 6) == 0) {
            struct Gasto g;
            if (n >= MAX_GASTOS) continue;
            memset(&g, 0, sizeof g);
            if (sscanf(linea + 6, "%lu;%10[^;];%d;%lf;%ld;%lf;%79[^\n]",
                       &g.id, g.fecha, &g.cat, &g.monto, &g.km, &g.litros, g.desc) >= 6) {
                costos_limpiar_descripcion(g.desc);
                if (g.cat >= 0 && g.cat < 6 && costos_fecha_ok(g.fecha) && g.monto > 0 && g.km >= 0 && g.litros >= 0) {
                    if (g.cat == 0 && g.litros <= 0) continue;
                    gastos[n++] = g;
                    if (g.id >= siguiente_id) siguiente_id = g.id + 1;
                }
            }
        } else {
            struct Gasto g;
            if (n >= MAX_GASTOS) continue;
            memset(&g, 0, sizeof g);
            if (sscanf(linea, "%10[^;];%d;%lf;%ld;%lf;%79[^\n]",
                       g.fecha, &g.cat, &g.monto, &g.km, &g.litros, g.desc) >= 5) {
                costos_limpiar_descripcion(g.desc);
                if (g.cat >= 0 && g.cat < 6 && costos_fecha_ok(g.fecha) && g.monto > 0 && g.km >= 0 && g.litros >= 0) {
                    if (g.cat == 0 && g.litros <= 0) continue;
                    g.id = siguiente_id++;
                    gastos[n++] = g;
                }
            }
        }
    }
    fclose(f);

    for (i = 1; i < n; i++) {
        struct Gasto actual = gastos[i];
        int j = i - 1;
        while (j >= 0 && strcmp(gastos[j].fecha, actual.fecha) > 0) {
            gastos[j + 1] = gastos[j];
            j--;
        }
        gastos[j + 1] = actual;
    }
}

int costos_registrar_vehiculo(const char *marca_n, const char *modelo_n, const char *placa_n,
                              int anio_n, long odometro_n, char *error, size_t error_tam)
{
    int i;
    if (!marca_n || !modelo_n || !placa_n || marca_n[0] == '\0' || modelo_n[0] == '\0' || placa_n[0] == '\0') {
        set_error(error, error_tam, "Error: marca, modelo y placa son obligatorios.");
        return 0;
    }
    if (anio_n < 1900 || anio_n > 2100) {
        set_error(error, error_tam, "Error: anio invalido. Debe ser entre 1900 y 2100.");
        return 0;
    }
    if (odometro_n < 0) {
        set_error(error, error_tam, "Error: odometro inicial invalido.");
        return 0;
    }
    if (hay_vehiculo && n > 0) {
        for (i = 0; i < n; i++) {
            if (odometro_n > gastos[i].km) {
                char buf[256];
                snprintf(buf, sizeof buf, "Error: odometro inicial (%ld) mayor que km de gasto ID %lu (%ld).",
                         odometro_n, gastos[i].id, gastos[i].km);
                set_error(error, error_tam, buf);
                return 0;
            }
        }
    }
    strncpy(marca, marca_n, sizeof marca - 1); marca[sizeof marca - 1] = '\0';
    strncpy(modelo, modelo_n, sizeof modelo - 1); modelo[sizeof modelo - 1] = '\0';
    strncpy(placa, placa_n, sizeof placa - 1); placa[sizeof placa - 1] = '\0';
    anio = anio_n; odometro = odometro_n; hay_vehiculo = 1;
    if (!costos_guardar(error, error_tam)) return 0;
    set_error(error, error_tam, "Vehiculo registrado/actualizado correctamente.");
    return 1;
}

int costos_agregar_gasto(const char *fecha, int cat, double monto, long km, double litros,
                         const char *desc, unsigned long *id_out, char *error, size_t error_tam)
{
    struct Gasto g;
    int pos;
    char desc_tmp[512];

    if (!hay_vehiculo) { set_error(error, error_tam, "Primero debe registrar el vehiculo."); return 0; }
    if (n >= MAX_GASTOS) { set_error(error, error_tam, "Se alcanzo el limite de gastos."); return 0; }
    if (!costos_fecha_ok(fecha)) { set_error(error, error_tam, "Error de fecha. Use AAAA-MM-DD con fecha real."); return 0; }
    if (cat < 0 || cat >= 6) { set_error(error, error_tam, "Error: categoria invalida."); return 0; }
    if (monto <= 0) { set_error(error, error_tam, "Error: el monto debe ser mayor que cero."); return 0; }
    if (km < odometro) {
        char buf[200];
        snprintf(buf, sizeof buf, "Error: kilometraje (%ld) menor al odometro inicial (%ld).", km, odometro);
        set_error(error, error_tam, buf);
        return 0;
    }
    if (cat == 0 && litros <= 0) { set_error(error, error_tam, "Error: para combustible, los litros deben ser mayores que cero."); return 0; }
    if (cat != 0 && litros < 0) { set_error(error, error_tam, "Error: los litros deben ser >= 0."); return 0; }

    memset(&g, 0, sizeof g);
    strncpy(g.fecha, fecha, sizeof g.fecha - 1);
    g.cat = cat; g.monto = monto; g.km = km; g.litros = litros;
    if (desc) { strncpy(desc_tmp, desc, sizeof desc_tmp - 1); desc_tmp[sizeof desc_tmp - 1] = '\0'; }
    else desc_tmp[0] = '\0';
    costos_limpiar_descripcion(desc_tmp);
    strncpy(g.desc, desc_tmp, sizeof g.desc - 1); g.desc[sizeof g.desc - 1] = '\0';
    g.id = siguiente_id++;

    pos = n;
    while (pos > 0 && strcmp(gastos[pos - 1].fecha, g.fecha) > 0) {
        gastos[pos] = gastos[pos - 1];
        pos--;
    }
    gastos[pos] = g; n++;
    if (id_out) *id_out = g.id;
    if (!costos_guardar(error, error_tam)) return 0;
    {
        char buf[120];
        snprintf(buf, sizeof buf, "Gasto #%lu agregado y guardado.", g.id);
        set_error(error, error_tam, buf);
    }
    return 1;
}

int costos_eliminar_gasto(unsigned long id, char *error, size_t error_tam)
{
    int i, pos = -1;
    for (i = 0; i < n; i++) {
        if (gastos[i].id == id) { pos = i; break; }
    }
    if (pos < 0) { set_error(error, error_tam, "No existe un gasto con ese ID."); return 0; }
    for (i = pos; i < n - 1; i++) gastos[i] = gastos[i + 1];
    n--;
    if (!costos_guardar(error, error_tam)) return 0;
    {
        char buf[120];
        snprintf(buf, sizeof buf, "Gasto #%lu eliminado correctamente.", id);
        set_error(error, error_tam, buf);
    }
    return 1;
}

int costos_obtener_lista(char *buffer, size_t tam)
{
    int i;
    size_t usado = 0;
    int escrito;
    if (!buffer || tam == 0) return 0;
    buffer[0] = '\0';
    if (n == 0) {
        snprintf(buffer, tam, "No hay gastos registrados.");
        return 1;
    }
    escrito = snprintf(buffer + usado, tam - usado, "Lista de gastos (%d):\nID    Fecha      Categoria        Monto       Km   Litros  Descripcion\n", n);
    if (escrito < 0) return 0; usado += (size_t)escrito < tam - usado ? (size_t)escrito : tam - usado - 1;
    for (i = 0; i < n && usado + 1 < tam; i++) {
        escrito = snprintf(buffer + usado, tam - usado, "%-5lu %-10s %-15s %10.2f %8ld %8.2f  %s\n",
                           gastos[i].id, gastos[i].fecha, CATEGORIAS[gastos[i].cat],
                           gastos[i].monto, gastos[i].km, gastos[i].litros, gastos[i].desc);
        if (escrito < 0) break;
        if ((size_t)escrito >= tam - usado) { usado = tam - 1; break; }
        usado += (size_t)escrito;
    }
    buffer[tam - 1] = '\0';
    return 1;
}

int costos_obtener_reporte(char *buffer, size_t tam)
{
    double total = 0, por_categoria[6] = {0};
    long km_max = 0;
    int i;
    size_t usado = 0;
    int escrito;
    if (!buffer || tam == 0) return 0;
    buffer[0] = '\0';
    if (!hay_vehiculo) {
        snprintf(buffer, tam, "No hay vehiculo registrado. Registre un vehiculo para ver reportes.");
        return 1;
    }
    for (i = 0; i < n; i++) {
        total += gastos[i].monto;
        por_categoria[gastos[i].cat] += gastos[i].monto;
        if (gastos[i].km > km_max) km_max = gastos[i].km;
    }
    escrito = snprintf(buffer, tam, "Vehiculo: %s %s (%s, %d)\nGastos registrados: %d\n\n", marca, modelo, placa, anio, n);
    if (escrito < 0) return 0; usado = (size_t)escrito < tam ? (size_t)escrito : tam - 1;
    for (i = 0; i < 6 && usado + 1 < tam; i++) {
        escrito = snprintf(buffer + usado, tam - usado, "  %-15s %12.2f\n", CATEGORIAS[i], por_categoria[i]);
        if (escrito > 0 && (size_t)escrito < tam - usado) usado += (size_t)escrito; else { usado = tam - 1; break; }
    }
    if (usado + 1 < tam) {
        escrito = snprintf(buffer + usado, tam - usado, "  %-15s %12.2f\n", "TOTAL", total);
        if (escrito > 0 && (size_t)escrito < tam - usado) usado += (size_t)escrito; else usado = tam - 1;
    }
    if (n > 0 && usado + 1 < tam) {
        escrito = snprintf(buffer + usado, tam - usado, "  %-15s %12.2f\n", "Promedio", total / n);
        if (escrito > 0 && (size_t)escrito < tam - usado) usado += (size_t)escrito; else usado = tam - 1;
    }
    if (usado + 1 < tam) {
        if (n > 0 && km_max > odometro)
            escrito = snprintf(buffer + usado, tam - usado, "Costo por km: %.4f (km recorridos: %ld)\n", total / (double)(km_max - odometro), km_max - odometro);
        else
            escrito = snprintf(buffer + usado, tam - usado, "Costo por km: no disponible\n");
        if (escrito > 0 && (size_t)escrito < tam - usado) usado += (size_t)escrito;
    }
    buffer[tam - 1] = '\0';
    return 1;
}
