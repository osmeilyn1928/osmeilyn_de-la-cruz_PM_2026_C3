
#include <stdio.h>

#define MAX 50

int main() {
    float MAT[MAX][MAX];
    int M, N;
    int i, j;

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

    printf("\nRecorrido de la matriz por columnas:\n");

    for (j = 0; j < N; j++) {
        for (i = 0; i < M; i++) {
            printf("%.2f ", MAT[i][j]);
        }
    }

    printf("\n");

    return 0;
}