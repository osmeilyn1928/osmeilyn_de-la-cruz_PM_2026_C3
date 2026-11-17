#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "costos_core.h"

/* Versión de terminal refactorizada para reutilizar la lógica en costos_core.c/.h.
   Se conserva copia previa en "Costos de vehiculos_terminal_original.c". */

void leer(const char *msg, char *dest, size_t tam)
{
    char temporal[512];
    size_t len;
    printf("%s", msg);
    if (fgets(temporal, sizeof temporal, stdin) == NULL) {
        if (tam > 0) dest[0] = '\0';
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
    while (isspace((unsigned char)*fin)) fin++;
    return fin != t && *fin == '\0';
}

int leer_long(const char *msg, long *valor)
{
    char t[128];
    char *fin;
    leer(msg, t, sizeof t);
    if (t[0] == '\0') return 0;
    *valor = strtol(t, &fin, 10);
    while (isspace((unsigned char)*fin)) fin++;
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
    while (isspace((unsigned char)*fin)) fin++;
    if (fin == t || *fin != '\0') return 0;
    if (numero < min || numero > max) return 0;
    *valor = (int)numero;
    return 1;
}

void datos_vehiculo(void)
{
    char marca_n[40], modelo_n[40], placa_n[16];
    int anio_n;
    long km_inicial;
    char msg[256];

    leer("Marca: ", marca_n, sizeof marca_n);
    leer("Modelo: ", modelo_n, sizeof modelo_n);
    leer("Placa: ", placa_n, sizeof placa_n);
    if (!leer_int_rango("Anio del vehiculo (1900-2100): ", &anio_n, 1900, 2100)) {
        printf("Error: anio invalido. Debe ser un numero entre 1900 y 2100.\n");
        return;
    }
    if (!leer_long("Odometro inicial (km): ", &km_inicial)) {
        printf("Error: odometro inicial invalido. Debe ser un numero entero mayor o igual a 0.\n");
        return;
    }
    if (costos_registrar_vehiculo(marca_n, modelo_n, placa_n, anio_n, km_inicial, msg, sizeof msg))
        printf("%s\n", msg);
    else
        printf("%s\n", msg);
}

void nuevo_gasto(void)
{
    char fecha[11], desc[512];
    int categoria_opcion, i;
    double monto, litros = 0;
    long km;
    unsigned long id_out;
    char msg[256];

    if (!hay_vehiculo) { printf("Primero debe registrar el vehiculo.\n"); return; }
    if (n >= MAX_GASTOS) { printf("Se alcanzo el limite de gastos.\n"); return; }

    leer("Fecha (AAAA-MM-DD): ", fecha, sizeof fecha);
    for (i = 0; i < 6; i++) printf("  %d) %s\n", i + 1, CATEGORIAS[i]);
    if (!leer_int_rango("Categoria (1-6): ", &categoria_opcion, 1, 6)) {
        printf("Error: categoria invalida. Debe elegir un numero entre 1 y 6.\n");
        return;
    }
    if (!leer_double("Monto: ", &monto)) { printf("Error: el monto debe ser un numero mayor que cero.\n"); return; }
    if (!leer_long("Kilometraje del odometro: ", &km)) { printf("Error: kilometraje invalido. Debe ser un numero entero mayor o igual a 0.\n"); return; }
    if (categoria_opcion == 1) {
        if (!leer_double("Litros: ", &litros)) { printf("Error: para combustible, los litros deben ser mayores que cero.\n"); return; }
    } else {
        if (!leer_double("Litros (0 si no aplica): ", &litros)) { printf("Error: los litros deben ser un numero mayor o igual a 0.\n"); return; }
    }
    leer("Descripcion (maximo 79 bytes): ", desc, sizeof desc);

    if (costos_agregar_gasto(fecha, categoria_opcion - 1, monto, km, litros, desc, &id_out, msg, sizeof msg))
        printf("%s\n", msg);
    else
        printf("%s\n", msg);
}

void listar(void)
{
    char buffer[8192];
    costos_obtener_lista(buffer, sizeof buffer);
    printf("\n%s\n", buffer);
}

void eliminar(void)
{
    char t[64];
    char *fin;
    unsigned long id;
    char msg[256];
    leer("ID del gasto que desea eliminar: ", t, sizeof t);
    if (t[0] == '\0') { printf("Error: debe escribir un ID valido.\n"); return; }
    id = strtoul(t, &fin, 10);
    while (isspace((unsigned char)*fin)) fin++;
    if (fin == t || *fin != '\0' || t[0] == '-') { printf("Error: debe escribir un ID valido.\n"); return; }
    if (costos_eliminar_gasto(id, msg, sizeof msg)) printf("%s\n", msg);
    else printf("%s\n", msg);
}

void reportes(void)
{
    char buffer[4096];
    costos_obtener_reporte(buffer, sizeof buffer);
    printf("\n%s\n", buffer);
}

int main(void)
{
    int opcion;
    costos_cargar();
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
            case 1: datos_vehiculo(); break;
            case 2: nuevo_gasto(); break;
            case 3: listar(); break;
            case 4: eliminar(); break;
            case 5: reportes(); break;
            case 0: {
                char msg[256];
                if (!costos_guardar(msg, sizeof msg)) printf("%s\n", msg);
                printf("Datos guardados. Hasta luego.\n");
                break;
            }
            default: printf("Error: opcion no valida.\n"); break;
        }
    } while (opcion != 0);
    return 0;
}
