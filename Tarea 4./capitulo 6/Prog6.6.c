
#include <stdio.h>

#define MAX 50

void leerA(int A[MAX][MAX], int M, int N);
void leerB(int B[MAX][MAX], int M, int N);
void calcularC(int A[MAX][MAX], int B[MAX][MAX],
               int C[MAX][MAX], int M, int N);
void imprimirMatriz(int MAT[MAX][MAX], int filas, int columnas);

int main() {
    int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];
    int M, N;

    printf("Ingrese el numero de filas de A (M): ");
    scanf("%d", &M);

    printf("Ingrese el numero de columnas de A (N): ");
    scanf("%d", &N);

    if (M < 1 || M > 50 || N < 1 || N > 50) {
        printf("Las dimensiones deben estar entre 1 y 50.\n");
        return 1;
    }

    printf("\nIngrese los elementos de la matriz A (%d x %d):\n", M, N);
    leerA(A, M, N);

    printf("\nIngrese los elementos de la matriz B (%d x %d):\n", N, M);
    leerB(B, M, N);

    calcularC(A, B, C, M, N);

    printf("\nMatriz A:\n");
    imprimirMatriz(A, M, N);

    printf("\nMatriz B:\n");
    imprimirMatriz(B, N, M);

    printf("\nResultado C = A + B transpuesta:\n");
    imprimirMatriz(C, M, N);

    return 0;
}

void leerA(int A[MAX][MAX], int M, int N) {
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("A[%d][%d]: ", i, j);
            scanf("%d", &A[i][j]);
        }
    }
}

void leerB(int B[MAX][MAX], int M, int N) {
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            printf("B[%d][%d]: ", i, j);
            scanf("%d", &B[i][j]);
        }
    }
}

void calcularC(int A[MAX][MAX], int B[MAX][MAX],
               int C[MAX][MAX], int M, int N) {
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = A[i][j] + B[j][i];
        }
    }
}

void imprimirMatriz(int MAT[MAX][MAX], int filas, int columnas) {
    int i, j;

    for (i = 0; i < filas; i++) {
        for (j = 0; j < columnas; j++) {
            printf("%d\t", MAT[i][j]);
        }
        printf("\n");
    }
}
