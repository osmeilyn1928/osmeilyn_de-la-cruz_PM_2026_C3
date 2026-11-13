
#include <stdio.h>

float promedio(float ALU[], int N) {
    int i;
    float suma = 0;

    for (i = 0; i < N; i++) {
        suma = suma + ALU[i];
    }

    return suma / N;
}

float porcentajeAprobados(float ALU[], int N) {
    int i, aprobados = 0;

    for (i = 0; i < N; i++) {
        if (ALU[i] > 1300) {
            aprobados++;
        }
    }

    return (float) aprobados * 100 / N;
}

int contar1500(float ALU[], int N) {
    int i, contador = 0;

    for (i = 0; i < N; i++) {
        if (ALU[i] >= 1500) {
            contador++;
        }
    }

    return contador;
}

int main(void) {
    float ALU[100];
    int N, i;

    printf("Cantidad de alumnos (1-100): ");
    scanf("%d", &N);

    if (N < 1 || N > 100) {
        printf("Cantidad invalida.\n");
        return 0;
    }

    for (i = 0; i < N; i++) {
        printf("Calificacion del alumno %d: ", i + 1);
        scanf("%f", &ALU[i]);
    }

    printf("\nPromedio general: %.2f\n",
           promedio(ALU, N));

    printf("Porcentaje de aprobados: %.2f%%\n",
           porcentajeAprobados(ALU, N));

    printf("Alumnos con 1500 puntos o mas: %d\n",
           contar1500(ALU, N));

    return 0;
}
