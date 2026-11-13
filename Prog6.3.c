
#include <stdio.h>

#define MAX 50

void leerMatriz(float MAT[MAX][MAX], int M, int N) {
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("Elemento [%d][%d]: ", i + 1, j + 1);
            scanf("%f", &MAT[i][j]);
        }
    }
}

void intercambiarFilas(float MAT[MAX][MAX], int M, int N) {
    int i, j;
    float aux;

    for (i = 0; i < M / 2; i++) {
        for (j = 0; j < N; j++) {
            aux = MAT[i][j];
            MAT[i][j] = MAT[M - 1 - i][j];
            MAT[M - 1 - i][j] = aux;
        }
    }
}

void imprimirMatriz(float MAT[MAX][MAX], int M, int N) {
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("%.2f\t", MAT[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    float MAT[MAX][MAX];
    int M, N;

    printf("Cantidad de filas (1-50): ");
    scanf("%d", &M);

    printf("Cantidad de columnas (1-50): ");
    scanf("%d", &N);

    if (M < 1 || M > MAX || N < 1 || N > MAX) {
        printf("Dimensiones invalidas.\n");
        return 1;
    }

    printf("\nIngrese los elementos de la matriz:\n");
    leerMatriz(MAT, M, N);

    printf("\nMatriz original:\n");
    imprimirMatriz(MAT, M, N);

    intercambiarFilas(MAT, M, N);

    printf("\nMatriz con las filas intercambiadas:\n");
    imprimirMatriz(MAT, M, N);

    return 0;
}
