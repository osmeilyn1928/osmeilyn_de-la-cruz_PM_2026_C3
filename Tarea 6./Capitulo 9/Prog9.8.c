
#include <stdio.h>

struct Alumno {
    int matricula;
    float cal1;
    float cal2;
    float cal3;
};

int main(void) {
    FILE *archivo;
    FILE *nuevo;
    struct Alumno alumnos[1000];
    struct Alumno aux;
    int n = 0;
    int i, j;

    archivo = fopen("arc.dat", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir arc.dat\n");
        return 1;
    }

    while (n < 1000 &&
           fscanf(archivo, "%d %f %f %f",
                  &alumnos[n].matricula,
                  &alumnos[n].cal1,
                  &alumnos[n].cal2,
                  &alumnos[n].cal3) == 4) {
        n++;
    }

    fclose(archivo);

    /* Ordenar las matriculas de menor a mayor */
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (alumnos[j].matricula >
                alumnos[j + 1].matricula) {

                aux = alumnos[j];
                alumnos[j] = alumnos[j + 1];
                alumnos[j + 1] = aux;
            }
        }
    }

    nuevo = fopen("arc1.dat", "w");

    if (nuevo == NULL) {
        printf("No se pudo crear arc1.dat\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        fprintf(nuevo, "%d %.1f %.1f %.1f\n",
                alumnos[i].matricula,
                alumnos[i].cal1,
                alumnos[i].cal2,
                alumnos[i].cal3);
    }

    fclose(nuevo);

    printf("Archivo ordenado correctamente.\n");

    return 0;
}
