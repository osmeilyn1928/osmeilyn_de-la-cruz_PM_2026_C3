
#include <stdio.h>

#define MAX 50

int main() {
    float MAT[MAX][MAX];
    int M, N;
    int i, j;
    int arriba, abajo, izquierda, derecha;

    printf("Ingrese el numero de filas (M): ");
    scanf("%d", &M);

    printf("Ingrese el numero de columnas (N): ");
    scanf("%d", &N);

    if (M < 1 || M > 50 || N < 1 || N > 50) {
        printf("Las dimensiones deben estar entre 1 y 50.\n");
        return 1;
    }

    printf("\nIngrese los elementos de la matriz:\n");

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("MAT[%d][%d]: ", i, j);
            scanf("%f", &MAT[i][j]);
        }
    }

    arriba = 0;
    abajo = M - 1;
    izquierda = 0;
    derecha = N - 1;

    printf("\nRecorrido en espiral:\n");

    while (arriba <= abajo && izquierda <= derecha) {

        for (j = izquierda; j <= derecha; j++) {
            printf("%.2f ", MAT[arriba][j]);
        }
        arriba++;

        for (i = arriba; i <= abajo; i++) {
            printf("%.2f ", MAT[i][derecha]);
        }
        derecha--;

        if (arriba <= abajo) {
            for (j = derecha; j >= izquierda; j--) {
                printf("%.2f ", MAT[abajo][j]);
            }
            abajo--;
        }

        if (izquierda <= derecha) {
            for (i = abajo; i >= arriba; i--) {
                printf("%.2f ", MAT[i][izquierda]);
            }
            izquierda++;
        }
    }

    printf("\n");

    return 0;
}
