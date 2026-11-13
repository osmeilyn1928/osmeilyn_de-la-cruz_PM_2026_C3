
#include <stdio.h>

#define MAX 50

void leerMatriz(float MAT[MAX][MAX], int F, int C) {
    int i, j;

    for (i = 0; i < F; i++) {
        for (j = 0; j < C; j++) {
            printf("Elemento [%d][%d]: ", i + 1, j + 1);
            scanf("%f", &MAT[i][j]);
        }
    }
}

void multiplicar(float A[MAX][MAX], float B[MAX][MAX],
                 float C[MAX][MAX], int M, int N, int P) {
    int i, j, k;

    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            C[i][j] = 0;

            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void imprimirMatriz(float MAT[MAX][MAX], int F, int C) {
    int i, j;

    for (i = 0; i < F; i++) {
        for (j = 0; j < C; j++) {
            printf("%.2f\t", MAT[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    float A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int M, N, P;

    printf("Cantidad de filas de A (M): ");
    scanf("%d", &M);

    printf("Cantidad de columnas de A (N): ");
    scanf("%d", &N);

    printf("Cantidad de columnas de B (P): ");
    scanf("%d", &P);

    if (M < 1 || M > MAX || N < 1 || N > MAX ||
        P < 1 || P > MAX) {
        printf("Dimensiones invalidas.\n");
        return 1;
    }

    printf("\nIngrese los elementos de A:\n");
    leerMatriz(A, M, N);

    printf("\nIngrese los elementos de B:\n");
    leerMatriz(B, N, P);

    multiplicar(A, B, C, M, N, P);

    printf("\nMatriz A:\n");
    imprimirMatriz(A, M, N);

    printf("\nMatriz B:\n");
    imprimirMatriz(B, N, P);

    printf("\nResultado de A x B:\n");
    imprimirMatriz(C, M, P);

    return 0;
}
