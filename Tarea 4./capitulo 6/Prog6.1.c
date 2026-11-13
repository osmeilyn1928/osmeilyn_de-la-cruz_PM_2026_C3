
#include <stdio.h>

void llenarMatriz(int MAT[100][100], int N) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i == j || i + j == N - 1) {
                MAT[i][j] = 1;
            } else {
                MAT[i][j] = 0;
            }
        }
    }
}

void imprimirMatriz(int MAT[100][100], int N) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%d ", MAT[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int MAT[100][100];
    int N;

    printf("Introduce el tamaño de la matriz (1-100): ");
    scanf("%d", &N);

    if (N < 1 || N > 100) {
        printf("El tamaño debe estar entre 1 y 100.\n");
        return 1;
    }

    llenarMatriz(MAT, N);

    printf("\nMatriz resultante:\n");
    imprimirMatriz(MAT, N);

    return 0;
}
