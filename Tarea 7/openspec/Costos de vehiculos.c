
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_GASTOS 500
#define ARCHIVO "vehiculo_simple.txt"
#define MAX_DESC 79

const char *CATEGORIAS[6] = {
    "Combustible", "Mantenimiento", "Reparacion",
    "Seguro", "Impuestos", "Otros"
};

struct Gasto {
    unsigned long id;
    char fecha[11];
    int cat;
    double monto;
    long km;
    double litros;
    char desc[MAX_DESC + 1];
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

void leer(const char *msg, char *dest, size_t tam)
{
    char temporal[512];
    size_t len;

    printf("%s", msg);

    if (fgets(temporal, sizeof temporal, stdin) == NULL) {
        dest[0] = '\0';
        return;
    }

    len = strcspn(temporal, "\r\n");
    temporal[len] = '\0';

    if (tam == 0) return;

    if (len >= tam) len = tam - 1;

    memcpy(dest, temporal, len);
    dest[len] = '\0';
}

int leer_double(const char *msg, double *valor)
{
    char t[128];
    char *fin;

    leer(msg, t, sizeof t);

    if (t[0] == '\0') return 0;

    *valor = strtod(t, &fin);

    while (isspace((unsigned char)*fin)) {
        fin++;
    }

    return fin != t && *fin == '\0';
}

int leer_long(const char *msg, long *valor)
{
    char t[128];
    char *fin;

    leer(msg, t, sizeof t);

    if (t[0] == '\0') return 0;

    *valor = strtol(t, &fin, 10);

    while (isspace((unsigned char)*fin)) {
        fin++;
    }

    if (fin == t || *fin != '\0') return 0;
    if (*valor < 0) return 0;

    return 1;
}

int leer_int_rango(const char *msg, int *valor, int min, int max)
{
    char t[64];
    char *fin;
    long numero;

    leer(msg, t, sizeof t);

    if (t[0] == '\0') return 0;

    numero = strtol(t, &fin, 10);

    while (isspace((unsigned char)*fin)) {
        fin++;
    }

    if (fin == t || *fin != '\0') return 0;
    if (numero < min || numero > max) return 0;

    *valor = (int)numero;
    return 1;
}

int fecha_ok(const char *f)
{
    int a, m, d;
    int dias_mes[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };
    int i;

    if (strlen(f) != 10) return 0;

    for (i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (f[i] != '-') return 0;
        } else if (!isdigit((unsigned char)f[i])) {
            return 0;
        }
    }

    if (sscanf(f, "%4d-%2d-%2d", &a, &m, &d) != 3) {
        return 0;
    }

    if (a < 1900 || m < 1 || m > 12) return 0;

    if (a % 4 == 0 &&
        (a % 100 != 0 || a % 400 == 0)) {
        dias_mes[1] = 29;
    }

    return d >= 1 && d <= dias_mes[m - 1];
}

void limitar_utf8(char *s, size_t max_bytes)
{
    size_t len = strlen(s);
    size_t corte;

    if (len <= max_bytes) return;

    corte = max_bytes;

    while (corte > 0 &&
           (((unsigned char)s[corte] & 0xC0U) == 0x80U)) {
        corte--;
    }

    s[corte] = '\0';
}

void limpiar_descripcion(char *s)
{
    size_t i;

    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == '|' || s[i] == ';' ||
            s[i] == '\n' || s[i] == '\r') {
            s[i] = ',';
        }
    }

    limitar_utf8(s, MAX_DESC);
}

void guardar(void)
{
    FILE *f = fopen(ARCHIVO, "w");
    int i;

    if (f == NULL) {
        printf("Error: no se pudo guardar el archivo '%s'. Verifique permisos o espacio disponible.\n", ARCHIVO);
        return;
    }

    fprintf(f, "VEHICULO;%s;%s;%s;%d;%ld;%lu\n",
            marca, modelo, placa, anio,
            odometro, siguiente_id);

    for (i = 0; i < n; i++) {
        fprintf(f,
                "GASTO;%lu;%s;%d;%.2f;%ld;%.2f;%s\n",
                gastos[i].id,
                gastos[i].fecha,
                gastos[i].cat,
                gastos[i].monto,
                gastos[i].km,
                gastos[i].litros,
                gastos[i].desc);
    }

    if (fclose(f) != 0) {
        printf("Advertencia: hubo un problema al cerrar el archivo '%s'.\n", ARCHIVO);
    }
}

void cargar(void)
{
    FILE *f = fopen(ARCHIVO, "r");
    char linea[512];

    if (f == NULL) return;

    while (fgets(linea, sizeof linea, f) != NULL) {
        linea[strcspn(linea, "\r\n")] = '\0';

        if (strncmp(linea, "VEHICULO;", 9) == 0) {
            char marca_tmp[40] = "", modelo_tmp[40] = "", placa_tmp[16] = "";
            int anio_tmp = 0;
            long odometro_tmp = 0;
            unsigned long prox = 1;

            if (sscanf(linea + 9,
                       "%39[^;];%39[^;];%15[^;];%d;%ld;%lu",
                       marca_tmp, modelo_tmp, placa_tmp, &anio_tmp,
                       &odometro_tmp, &prox) >= 5) {
                strncpy(marca, marca_tmp, sizeof marca - 1);
                marca[sizeof marca - 1] = '\0';
                strncpy(modelo, modelo_tmp, sizeof modelo - 1);
                modelo[sizeof modelo - 1] = '\0';
                strncpy(placa, placa_tmp, sizeof placa - 1);
                placa[sizeof placa - 1] = '\0';
                anio = anio_tmp;
                odometro = odometro_tmp;
                hay_vehiculo = 1;

                if (prox > 0) {
                    siguiente_id = prox;
                }
            }
        } else if (strncmp(linea, "GASTO;", 6) == 0) {
            struct Gasto g;

            if (n >= MAX_GASTOS) {
                continue;
            }

            memset(&g, 0, sizeof g);

            if (sscanf(linea + 6,
                       "%lu;%10[^;];%d;%lf;%ld;%lf;%79[^\n]",
                       &g.id, g.fecha, &g.cat, &g.monto,
                       &g.km, &g.litros, g.desc) >= 6) {
                limpiar_descripcion(g.desc);
                if (g.cat >= 0 && g.cat < 6 &&
                    fecha_ok(g.fecha) &&
                    g.monto > 0 && g.km >= 0 && g.litros >= 0) {
                    if (g.cat == 0 && g.litros <= 0) {
                        continue;
                    }
                    gastos[n++] = g;

                    if (g.id >= siguiente_id) {
                        siguiente_id = g.id + 1;
                    }
                }
            }
        } else {
            struct Gasto g;

            if (n >= MAX_GASTOS) {
                continue;
            }

            memset(&g, 0, sizeof g);

            if (sscanf(linea,
                       "%10[^;];%d;%lf;%ld;%lf;%79[^\n]",
                       g.fecha, &g.cat, &g.monto,
                       &g.km, &g.litros, g.desc) >= 5) {
                limpiar_descripcion(g.desc);
                if (g.cat >= 0 && g.cat < 6 &&
                    fecha_ok(g.fecha) &&
                    g.monto > 0 && g.km >= 0 && g.litros >= 0) {
                    if (g.cat == 0 && g.litros <= 0) {
                        continue;
                    }
                    g.id = siguiente_id++;
                    gastos[n++] = g;
                }
            }
        }
    }

    fclose(f);

    for (int i = 1; i < n; i++) {
        struct Gasto actual = gastos[i];
        int j = i - 1;

        while (j >= 0 &&
               strcmp(gastos[j].fecha, actual.fecha) > 0) {
            gastos[j + 1] = gastos[j];
            j--;
        }

        gastos[j + 1] = actual;
    }
}

void datos_vehiculo(void)
{
    char marca_nueva[40];
    char modelo_nuevo[40];
    char placa_nueva[16];
    int anio_nuevo;
    long km_inicial;
    int i;

    leer("Marca: ", marca_nueva, sizeof marca_nueva);
    leer("Modelo: ", modelo_nuevo, sizeof modelo_nuevo);
    leer("Placa: ", placa_nueva, sizeof placa_nueva);

    if (!leer_int_rango("Anio del vehiculo (1900-2100): ", &anio_nuevo, 1900, 2100)) {
        printf("Error: anio invalido. Debe ser un numero entre 1900 y 2100.\n");
        return;
    }

    if (!leer_long("Odometro inicial (km): ", &km_inicial)) {
        printf("Error: odometro inicial invalido. Debe ser un numero entero mayor o igual a 0.\n");
        return;
    }

    if (marca_nueva[0] == '\0' ||
        modelo_nuevo[0] == '\0' ||
        placa_nueva[0] == '\0') {
        printf("Error: marca, modelo y placa son obligatorios.\n");
        return;
    }

    if (hay_vehiculo && n > 0) {
        for (i = 0; i < n; i++) {
            if (km_inicial > gastos[i].km) {
                printf("Error: el odometro inicial (%ld) no puede ser mayor que el kilometraje de un gasto registrado (%ld, ID %lu).\n",
                       km_inicial, gastos[i].km, gastos[i].id);
                return;
            }
        }
    }

    strncpy(marca, marca_nueva, sizeof marca - 1);
    marca[sizeof marca - 1] = '\0';
    strncpy(modelo, modelo_nuevo, sizeof modelo - 1);
    modelo[sizeof modelo - 1] = '\0';
    strncpy(placa, placa_nueva, sizeof placa - 1);
    placa[sizeof placa - 1] = '\0';
    anio = anio_nuevo;
    odometro = km_inicial;
    hay_vehiculo = 1;

    printf("Vehiculo registrado/actualizado correctamente.\n");

    guardar();
}

void nuevo_gasto(void)
{
    struct Gasto g;
    long km;
    int i, pos, categoria_opcion;

    if (!hay_vehiculo) {
        printf("Primero debe registrar el vehiculo.\n");
        return;
    }

    if (n >= MAX_GASTOS) {
        printf("Se alcanzo el limite de gastos.\n");
        return;
    }

    memset(&g, 0, sizeof g);

    leer("Fecha (AAAA-MM-DD): ", g.fecha, sizeof g.fecha);

    if (!fecha_ok(g.fecha)) {
        printf("Error de fecha. Use el formato AAAA-MM-DD con una fecha real.\n");
        return;
    }

    for (i = 0; i < 6; i++) {
        printf("  %d) %s\n", i + 1, CATEGORIAS[i]);
    }

    if (!leer_int_rango("Categoria (1-6): ", &categoria_opcion, 1, 6)) {
        printf("Error: categoria invalida. Debe elegir un numero entre 1 y 6.\n");
        return;
    }

    g.cat = categoria_opcion - 1;

    if (!leer_double("Monto: ", &g.monto) ||
        g.monto <= 0) {
        printf("Error: el monto debe ser un numero mayor que cero.\n");
        return;
    }

    if (!leer_long("Kilometraje del odometro: ", &km)) {
        printf("Error: kilometraje invalido. Debe ser un numero entero mayor o igual a 0.\n");
        return;
    }

    if (km < odometro) {
        printf("Error: el kilometraje (%ld) no puede ser menor al odometro inicial (%ld).\n", km, odometro);
        return;
    }

    g.km = km;

    if (g.cat == 0) {
        if (!leer_double("Litros: ", &g.litros) ||
            g.litros <= 0) {
            printf("Error: para combustible, los litros deben ser mayores que cero.\n");
            return;
        }
    } else {
        if (!leer_double("Litros (0 si no aplica): ", &g.litros) ||
            g.litros < 0) {
            printf("Error: los litros deben ser un numero mayor o igual a 0.\n");
            return;
        }
    }

    {
        char descripcion[512];

        leer("Descripcion (maximo 79 bytes): ",
             descripcion, sizeof descripcion);

        limpiar_descripcion(descripcion);

        strncpy(g.desc, descripcion, sizeof g.desc - 1);
        g.desc[sizeof g.desc - 1] = '\0';
    }

    g.id = siguiente_id++;

    pos = n;

    while (pos > 0 &&
           strcmp(gastos[pos - 1].fecha, g.fecha) > 0) {
        gastos[pos] = gastos[pos - 1];
        pos--;
    }

    gastos[pos] = g;
    n++;

    guardar();

    printf("Gasto #%lu agregado y guardado.\n", g.id);
}

void listar(void)
{
    int i;

    if (n == 0) {
        printf("No hay gastos registrados.\n");
        return;
    }

    printf("\n--- Lista de gastos (%d registrado%s) ---\n",
           n, n == 1 ? "" : "s");
    printf("%-5s %-10s %-15s %10s %10s %8s  %s\n",
           "ID", "Fecha", "Categoria", "Monto",
           "Km", "Litros", "Descripcion");

    for (i = 0; i < n; i++) {
        printf("%-5lu %-10s %-15s %10.2f %10ld %8.2f  %s\n",
               gastos[i].id,
               gastos[i].fecha,
               CATEGORIAS[gastos[i].cat],
               gastos[i].monto,
               gastos[i].km,
               gastos[i].litros,
               gastos[i].desc);
    }
}

void eliminar(void)
{
    char t[64];
    char *fin;
    unsigned long id;
    int i, pos = -1;

    leer("ID del gasto que desea eliminar: ", t, sizeof t);

    if (t[0] == '\0') {
        printf("Error: debe escribir un ID valido.\n");
        return;
    }

    id = strtoul(t, &fin, 10);

    while (isspace((unsigned char)*fin)) {
        fin++;
    }

    if (fin == t || *fin != '\0' || t[0] == '-') {
        printf("Error: debe escribir un ID valido.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        if (gastos[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos < 0) {
        printf("No existe un gasto con ese ID.\n");
        return;
    }

    for (i = pos; i < n - 1; i++) {
        gastos[i] = gastos[i + 1];
    }

    n--;

    guardar();

    printf("Gasto #%lu eliminado correctamente.\n", id);
}

void reportes(void)
{
    double total = 0;
    double por_categoria[6] = {0};
    long km_max = 0;
    int i;

    if (!hay_vehiculo) {
        printf("No hay vehiculo registrado. Registre un vehiculo para ver reportes.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        total += gastos[i].monto;
        por_categoria[gastos[i].cat] += gastos[i].monto;

        if (gastos[i].km > km_max) {
            km_max = gastos[i].km;
        }
    }

    printf("\n--- Reporte de costos ---\n");
    printf("Vehiculo: %s %s (%s, %d)\n", marca, modelo, placa, anio);
    printf("Gastos registrados: %d\n\n", n);

    for (i = 0; i < 6; i++) {
        printf("  %-15s %12.2f\n",
               CATEGORIAS[i], por_categoria[i]);
    }

    printf("  %-15s %12.2f\n", "TOTAL", total);

    if (n > 0) {
        printf("  %-15s %12.2f\n", "Promedio", total / n);
    }

    if (n > 0 && km_max > odometro) {
        printf("Costo por km: %.4f (km recorridos: %ld)\n",
               total / (double)(km_max - odometro), km_max - odometro);
    } else {
        printf("Costo por km: no disponible (se requieren gastos y km recorridos mayores al odometro inicial)\n");
    }
}

int main(void)
{
    int opcion;

    cargar();

    do {
        printf("\n== Gestion de costos del vehiculo ==\n");
        printf("1) Registrar/editar vehiculo\n");
        printf("2) Registrar gasto\n");
        printf("3) Listar gastos\n");
        printf("4) Eliminar gasto por ID\n");
        printf("5) Reportes\n");
        printf("0) Guardar y salir\n");

        if (!leer_int_rango("Opcion: ", &opcion, 0, 5)) {
            printf("Error: opcion no valida. Debe elegir un numero entre 0 y 5.\n");
            continue;
        }

        switch (opcion) {
            case 1:
                datos_vehiculo();
                break;

            case 2:
                nuevo_gasto();
                break;

            case 3:
                listar();
                break;

            case 4:
                eliminar();
                break;

            case 5:
                reportes();
                break;

            case 0:
                guardar();
                printf("Datos guardados. Hasta luego.\n");
                break;

            default:
                printf("Error: opcion no valida.\n");
                break;
        }

    } while (opcion != 0);

    return 0;
}
