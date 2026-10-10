#include <stdio.h>

int main(void) {
    float promedio;

    printf("Ingrese el promedio del alumno: ");
    scanf("%f", &promedio);

    if (promedio >= 6) {
        printf("Aprobado\n");
    }

    return 0;
}