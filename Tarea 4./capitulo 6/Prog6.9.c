
#include <stdio.h>

#define N 8

int tablero[N][N];

int esValida(int fila, int columna) {
    int i, j;

    /* Revisar la misma columna */
    for (i = 0; i < fila; i++) {
        if (tablero[i][columna] == 1) {
            return 0;
        }
    }

    /* Revisar la diagonal superior izquierda */
    for (i = fila - 1, j = columna - 1;
         i >= 0 && j >= 0; i--, j--) {
        if (tablero[i][j] == 1) {
            return 0;
        }
    }

    /* Revisar la diagonal superior derecha */
    for (i = fila - 1, j = columna + 1;
         i >= 0 && j < N; i--, j++) {
        if (tablero[i][j] == 1) {
            return 0;
        }
    }

    return 1;
}

int colocarReinas(int fila) {
    int columna;

    if (fila == N) {
        return 1;
    }

    for (columna = 0; columna < N; columna++) {
        if (esValida(fila, columna)) {
            tablero[fila][columna] = 1;

            if (colocarReinas(fila + 1)) {
                return 1;
            }

            tablero[fila][columna] = 0;
        }
    }

    return 0;
}

void imprimirTablero() {
    int i, j;

    printf("\nSolucion encontrada:\n\n");

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (tablero[i][j] == 1) {
                printf(" R ");
            } else {
                printf(" . ");
            }
        }
        printf("\n");
    }
}

int main() {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            tablero[i][j] = 0;
        }
    }

    if (colocarReinas(0)) {
        imprimirTablero();
    } else {
        printf("No se encontro una solucion.\n");
    }

    return 0;
}
