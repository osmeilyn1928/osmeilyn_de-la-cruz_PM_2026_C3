
#include <stdio.h>

#define MAX 100

void leerMatriz(int CUA[MAX][MAX], int N) {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("Elemento [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &CUA[i][j]);
        }
    }
}

int esMagico(int CUA[MAX][MAX], int N) {
    int i, j, suma, referencia;
    int diagonal1 = 0, diagonal2 = 0;
    int vistos[MAX * MAX + 1] = {0};

    /* Verificar que los numeros sean de 1 a N*N
       y que no se repitan. */
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            int valor = CUA[i][j];

            if (valor < 1 || valor > N * N)
                return 0;

            if (vistos[valor] == 1)
                return 0;

            vistos[valor] = 1;
        }
    }

    /* Suma de la primera fila como referencia. */
    referencia = 0;
    for (j = 0; j < N; j++)
        referencia += CUA[0][j];

    /* Verificar las filas. */
    for (i = 0; i < N; i++) {
        suma = 0;
        for (j = 0; j < N; j++)
            suma += CUA[i][j];

        if (suma != referencia)
            return 0;
    }

    /* Verificar las columnas. */
    for (j = 0; j < N; j++) {
        suma = 0;
        for (i = 0; i < N; i++)
            suma += CUA[i][j];

        if (suma != referencia)
            return 0;
    }

    /* Verificar las dos diagonales principales. */
    for (i = 0; i < N; i++) {
        diagonal1 += CUA[i][i];
        diagonal2 += CUA[i][N - 1 - i];
    }

    if (diagonal1 != referencia ||
        diagonal2 != referencia)
        return 0;

    return 1;
}

int main(void) {
    int CUA[MAX][MAX];
    int N;

    printf("Ingrese un orden impar (1-99): ");
    scanf("%d", &N);

    if (N < 1 || N > MAX || N % 2 == 0) {
        printf("El orden debe ser impar y estar entre 1 y 100.\n");
        return 1;
    }

    printf("\nIngrese los elementos de la matriz:\n");
    leerMatriz(CUA, N);

    if (esMagico(CUA, N))
        printf("\nLa matriz es un cuadrado magico.\n");
    else
        printf("\nLa matriz no es un cuadrado magico.\n");

    return 0;
}
