#ifndef COSTOS_CORE_H
#define COSTOS_CORE_H

#include <stddef.h>

#define MAX_GASTOS 500
#define MAX_DESC 79
#define ARCHIVO_DATOS "vehiculo_simple.txt"

extern const char *CATEGORIAS[6];

struct Gasto {
    unsigned long id;
    char fecha[11];
    int cat;
    double monto;
    long km;
    double litros;
    char desc[MAX_DESC + 1];
};

extern char marca[40];
extern char modelo[40];
extern char placa[16];
extern int anio;
extern int hay_vehiculo;
extern long odometro;
extern struct Gasto gastos[MAX_GASTOS];
extern int n;
extern unsigned long siguiente_id;

void costos_cargar(void);
int costos_guardar(char *error, size_t error_tam);
int costos_fecha_ok(const char *f);
void costos_limpiar_descripcion(char *s);

int costos_registrar_vehiculo(const char *marca_n, const char *modelo_n, const char *placa_n,
                              int anio_n, long odometro_n, char *error, size_t error_tam);
int costos_agregar_gasto(const char *fecha, int cat, double monto, long km, double litros,
                         const char *desc, unsigned long *id_out, char *error, size_t error_tam);
int costos_eliminar_gasto(unsigned long id, char *error, size_t error_tam);

int costos_obtener_reporte(char *buffer, size_t tam);
int costos_obtener_lista(char *buffer, size_t tam);

#endif
