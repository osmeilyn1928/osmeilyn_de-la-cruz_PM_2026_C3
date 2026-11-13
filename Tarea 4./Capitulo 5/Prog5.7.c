
#include <stdio.h>

float calcularPromedio(float VEC[], int N) {
    int i;
    float suma = 0;

    for (i = 0; i < N; i++) {
        suma = suma + VEC[i];
    }

    return suma / N;
}

int contarMeses(float VEC[], int N, float promedio) {
    int i, contador = 0;

    for (i = 0; i < N; i++) {
        if (VEC[i] > promedio) {
            contador++;
        }
    }

    return contador;
}

int buscarMayor(float VEC[], int N) {
    int i, pos = 0;

    for (i = 1; i < N; i++) {
        if (VEC[i] > VEC[pos]) {
            pos = i;
        }
    }

    return pos;
}

int main(void) {
    float VEC[12], promedio;
    int i, meses, mayor;

    for (i = 0; i < 12; i++) {
        printf("Toneladas cosechadas en el mes %d: ", i + 1);
        scanf("%f", &VEC[i]);
    }

    promedio = calcularPromedio(VEC, 12);
    meses = contarMeses(VEC, 12, promedio);
    mayor = buscarMayor(VEC, 12);

    printf("\nPromedio anual: %.2f toneladas\n", promedio);

    printf("Meses con cosecha superior al promedio: %d\n",
           meses);

    printf("Mes con mayor cosecha: %d\n", mayor + 1);

    printf("Mayor cosecha: %.2f toneladas\n", VEC[mayor]);

    return 0;
}
