
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
    double numero;

    if (!leer_double(msg, &numero)) return 0;

    if (numero < 0 || numero > 2147483647.0) return 0;

    if (numero != (long)numero) return 0;

    *valor = (long)numero;

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
        printf("Error: no se pudo guardar el archivo.\n");
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

    fclose(f);
}

void cargar(void)
{
    FILE *f = fopen(ARCHIVO, "r");
    char linea[512];

    if (f == NULL) return;

    while (fgets(linea, sizeof linea, f) != NULL) {
        linea[strcspn(linea, "\r\n")] = '\0';

        if (strncmp(linea, "VEHICULO;", 9) == 0) {
            unsigned long prox = 1;

            if (sscanf(linea + 9,
                       "%39[^;];%39[^;];%15[^;];%d;%ld;%lu",
                       marca, modelo, placa, &anio,
                       &odometro, &prox) >= 5) {
                hay_vehiculo = 1;

                if (prox > 0) {
                    siguiente_id = prox;
                }
            }
        } else if (strncmp(linea, "GASTO;", 6) == 0 &&
                   n < MAX_GASTOS) {
            struct Gasto g;

            memset(&g, 0, sizeof g);

            if (sscanf(linea + 6,
                       "%lu;%10[^;];%d;%lf;%ld;%lf;%79[^\n]",
                       &g.id, g.fecha, &g.cat, &g.monto,
                       &g.km, &g.litros, g.desc) >= 6) {
                if (g.cat >= 0 && g.cat < 6 &&
                    fecha_ok(g.fecha)) {
                    gastos[n++] = g;

                    if (g.id >= siguiente_id) {
                        siguiente_id = g.id + 1;
                    }
                }
            }
        } else {
            struct Gasto g;

            memset(&g, 0, sizeof g);

            if (n < MAX_GASTOS &&
                sscanf(linea,
                       "%10[^;];%d;%lf;%ld;%lf;%79[^\n]",
                       g.fecha, &g.cat, &g.monto,
                       &g.km, &g.litros, g.desc) >= 5) {
                if (g.cat >= 0 && g.cat < 6 &&
                    fecha_ok(g.fecha)) {
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
    char t[64];
    double valor;
    long km_inicial;

    leer("Marca: ", marca, sizeof marca);
    leer("Modelo: ", modelo, sizeof modelo);
    leer("Placa: ", placa, sizeof placa);
    leer("Anio del vehiculo: ", t, sizeof t);

    anio = atoi(t);

    if (!leer_double("Odometro inicial (km): ", &valor) ||
        valor < 0 ||
        valor > 2147483647.0 ||
        valor != (long)valor) {
        printf("Odometro invalido.\n");
        hay_vehiculo = 0;
        return;
    }

    km_inicial = (long)valor;

    if (marca[0] == '\0' ||
        modelo[0] == '\0' ||
        placa[0] == '\0' ||
        anio < 1900 || anio > 2100) {
        printf("Datos del vehiculo invalidos.\n");
        hay_vehiculo = 0;
        return;
    }

    odometro = km_inicial;
    hay_vehiculo = 1;

    printf("Vehiculo registrado correctamente.\n");

    guardar();
}

void nuevo_gasto(void)
{
    struct Gasto g;
    char t[64];
    long km;
    int i, pos;

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
        printf("Error de fecha. Use AAAA-MM-DD.\n");
        return;
    }

    for (i = 0; i < 6; i++) {
        printf("  %d) %s\n", i + 1, CATEGORIAS[i]);
    }

    leer("Categoria (1-6): ", t, sizeof t);

    g.cat = atoi(t) - 1;

    if (g.cat < 0 || g.cat >= 6) {
        printf("Categoria invalida.\n");
        return;
    }

    if (!leer_double("Monto: ", &g.monto) ||
        g.monto <= 0) {
        printf("Error: el monto debe ser mayor que cero.\n");
        return;
    }

    if (!leer_long("Kilometraje del odometro: ", &km)) {
        printf("Error: kilometraje invalido.\n");
        return;
    }

    if (km < odometro) {
        printf("Error: kilometraje menor al inicial.\n");
        return;
    }

    g.km = km;

    if (g.cat == 0) {
        if (!leer_double("Litros: ", &g.litros) ||
            g.litros <= 0) {
            printf("Error: los litros deben ser mayores que cero.\n");
            return;
        }
    } else {
        if (!leer_double("Litros (0 si no aplica): ", &g.litros) ||
            g.litros < 0) {
            printf("Los litros no pueden ser negativos.\n");
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

    printf("\n%-5s %-10s %-15s %10s %10s %8s  %s\n",
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

    if (t[0] == '\0' || t[0] == '-') {
        printf("Debe escribir un ID valido.\n");
        return;
    }

    id = strtoul(t, &fin, 10);

    while (isspace((unsigned char)*fin)) {
        fin++;
    }

    if (*fin != '\0') {
        printf("Debe escribir un ID valido.\n");
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

    printf("Gasto #%lu eliminado.\n", id);
}

void reportes(void)
{
    double total = 0;
    double por_categoria[6] = {0};
    long km_max = 0;
    int i;

    for (i = 0; i < n; i++) {
        total += gastos[i].monto;
        por_categoria[gastos[i].cat] += gastos[i].monto;

        if (gastos[i].km > km_max) {
            km_max = gastos[i].km;
        }
    }

    printf("\n--- Resumen de gastos ---\n");

    for (i = 0; i < 6; i++) {
        printf("  %-15s %12.2f\n",
               CATEGORIAS[i], por_categoria[i]);
    }

    printf("  %-15s %12.2f\n", "TOTAL", total);

    if (hay_vehiculo && n > 0 && km_max > odometro) {
        printf("Costo por km: %.4f\n",
               total / (double)(km_max - odometro));
    } else {
        printf("Costo por km: no disponible\n");
    }
}

int main(void)
{
    char t[32];
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

        leer("Opcion: ", t, sizeof t);
        opcion = atoi(t);

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
                printf("Opcion no valida.\n");
                break;
        }

    } while (opcion != 0);

    return 0;
}
