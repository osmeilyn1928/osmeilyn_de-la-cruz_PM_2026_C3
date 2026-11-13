
#include <stdio.h>

void mostrar(int VEC[], int N) {
    int i;

    printf("Elementos del arreglo: ");
    for (i = 0; i < N; i++) {
        printf("%d ", VEC[i]);
    }
    printf("\n");
}

int buscar(int VEC[], int N, int ELE) {
    int i;

    for (i = 0; i < N; i++) {
        if (VEC[i] == ELE) {
            return i;
        }
    }

    return -1;
}

int main() {
    int VEC[100];
    int N, i, ELE, opcion, pos;

    printf("Cantidad de elementos: ");
    scanf("%d", &N);

    if (N < 1 || N > 100) {
        printf("Cantidad invalida.\n");
        return 0;
    }

    for (i = 0; i < N; i++) {
        printf("Introduce un numero: ");
        scanf("%d", &VEC[i]);
    }

    mostrar(VEC, N);

    printf("1. Insertar\n");
    printf("2. Eliminar\n");
    printf("Elige una opcion: ");
    scanf("%d", &opcion);

    printf("Introduce el numero: ");
    scanf("%d", &ELE);

    pos = buscar(VEC, N, ELE);

    if (opcion == 1) {
        if (pos != -1) {
            printf("El numero ya existe.\n");
        } else if (N == 100) {
            printf("El arreglo esta lleno.\n");
        } else {
            VEC[N] = ELE;
            N++;
        }
    } else if (opcion == 2) {
        if (pos == -1) {
            printf("El numero no existe.\n");
        } else {
            for (i = pos; i < N - 1; i++) {
                VEC[i] = VEC[i + 1];
            }
            N--;
        }
    } else {
        printf("Opcion invalida.\n");
        return 0;
    }

    mostrar(VEC, N);

    return 0;
}