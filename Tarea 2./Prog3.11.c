
#include <stdio.h>

int main(void) {
    int matricula, i;
    int mejorMatricula = 0, peorMatricula = 0;
    float calificacion, suma, promedio;
    float mejorPromedio = -1, peorPromedio = 11;

    printf("Ingrese la matricula del alumno (0 para terminar): ");
    scanf("%d", &matricula);

    while (matricula != 0) {
        suma = 0;

        for (i = 1; i <= 5; i++) {
            printf("Ingrese la calificacion %d: ", i);
            scanf("%f", &calificacion);
            suma = suma + calificacion;
        }

        promedio = suma / 5;

        printf("Matricula: %d | Promedio: %.2f\n", matricula, promedio);

        if (promedio > mejorPromedio) {
            mejorPromedio = promedio;
            mejorMatricula = matricula;
        }

        if (promedio < peorPromedio) {
            peorPromedio = promedio;
            peorMatricula = matricula;
        }

        printf("\nIngrese otra matricula (0 para terminar): ");
        scanf("%d", &matricula);
    }

    if (mejorMatricula != 0) {
        printf("\nMejor alumno: %d | Promedio: %.2f\n",
               mejorMatricula, mejorPromedio);

        printf("Peor alumno: %d | Promedio: %.2f\n",
               peorMatricula, peorPromedio);
    } else {
        printf("\nNo se ingresaron alumnos.\n");
    }

    return 0;
}
