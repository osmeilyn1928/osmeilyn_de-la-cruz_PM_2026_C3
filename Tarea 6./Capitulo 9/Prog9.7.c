
#include <stdio.h>
#include <string.h>

struct Alumno {
    int matricula;
    char nombre[50];
    int carrera;
    float promedio;
};

int main(void) {
    FILE *archivo;
    FILE *nuevo;
    struct Alumno alumno;
    struct Alumno anterior;
    int primero = 1;

    archivo = fopen("ad5.dat", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir ad5.dat\n");
        return 1;
    }

    nuevo = fopen("ad5_sin_repetidos.dat", "w");

    if (nuevo == NULL) {
        printf("No se pudo crear el archivo nuevo\n");
        fclose(archivo);
        return 1;
    }

    while (fscanf(archivo, "%d %49s %d %f",
                  &alumno.matricula,
                  alumno.nombre,
                  &alumno.carrera,
                  &alumno.promedio) == 4) {

        if (primero || alumno.matricula != anterior.matricula) {
            fprintf(nuevo, "%d %s %d %.2f\n",
                    alumno.matricula,
                    alumno.nombre,
                    alumno.carrera,
                    alumno.promedio);

            anterior = alumno;
            primero = 0;
        }
    }

    fclose(archivo);
    fclose(nuevo);

    printf("Se creo ad5_sin_repetidos.dat sin matriculas repetidas.\n");

    return 0;
}
