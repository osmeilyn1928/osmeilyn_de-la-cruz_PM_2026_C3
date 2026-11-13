
#include <stdio.h>

#define N 8

int tablero[N][N];

int movFila[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int movCol[8]  = { 1,  2, 2, 1, -1, -2, -2, -1};

int esValido(int fila, int columna) {
    return fila >= 0 && fila < N &&
           columna >= 0 && columna < N &&
           tablero[fila][columna] == 0;
}

int contarMovimientos(int fila, int columna) {
    int k, nuevaFila, nuevaColumna;
    int cantidad = 0;

    for (k = 0; k < 8; k++) {
        nuevaFila = fila + movFila[k];
        nuevaColumna = columna + movCol[k];

        if (esValido(nuevaFila, nuevaColumna)) {
            cantidad++;
        }
    }

    return cantidad;
}

int recorrer(int fila, int columna, int paso) {
    int k, j;
    int nuevaFila, nuevaColumna;
    int filas[8], columnas[8], grados[8];
    int total = 0;
    int temp;

    tablero[fila][columna] = paso;

    if (paso == N * N) {
        return 1;
    }

    /* Buscar los movimientos posibles */
    for (k = 0; k < 8; k++) {
        nuevaFila = fila + movFila[k];
        nuevaColumna = columna + movCol[k];

        if (esValido(nuevaFila, nuevaColumna)) {
            filas[total] = nuevaFila;
            columnas[total] = nuevaColumna;
            grados[total] = contarMovimientos(nuevaFila, nuevaColumna);
            total++;
        }
    }

    /* Probar primero las casillas con menos salidas posibles */
    for (k = 0; k < total - 1; k++) {
        for (j = k + 1; j < total; j++) {
            if (grados[j] < grados[k]) {
                temp = grados[k];
                grados[k] = grados[j];
                grados[j] = temp;

                temp = filas[k];
                filas[k] = filas[j];
                filas[j] = temp;

                temp = columnas[k];
                columnas[k] = columnas[j];
                columnas[j] = temp;
            }
        }
    }

    /* Intentar completar el recorrido */
    for (k = 0; k < total; k++) {
        if (recorrer(filas[k], columnas[k], paso + 1)) {
            return 1;
        }
    }

    /* Si no funciona, regresar y probar otra opción */
    tablero[fila][columna] = 0;

    return 0;
}

int main() {
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            tablero[i][j] = 0;
        }
    }

    if (recorrer(0, 0, 1)) {
        printf("Recorrido completo del caballo:\n\n");

        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                printf("%2d ", tablero[i][j]);
            }
            printf("\n");
        }

        printf("\nSe visitaron las 64 casillas una sola vez.\n");
    } else {
        printf("No se encontro un recorrido.\n");
    }

    return 0;
}
