
#include <stdio.h>

int buscar(int VEC[], int N, int ELE) {
    int i;

    for (i = 0; i < N; i++) {
        if (VEC[i] == ELE) {
            return i;
        }
    }

    return -1;
}

int insertar(int VEC[], int N, int ELE) {
    int i;

    if (N >= 100) {
        printf("El arreglo esta lleno.\n");
        return N;
    }

    if (buscar(VEC, N, ELE) != -1) {
        printf("El numero ya existe.\n");
        return N;
    }

    i = N - 1;

    while (i >= 0 && VEC[i] > ELE) {
        VEC[i + 1] = VEC[i];
        i--;
    }

    VEC[i + 1] = ELE;

    return N + 1;
}

int eliminar(int VEC[], int N, int ELE) {
    int pos, i;

    pos = buscar(VEC, N, ELE);

    if (pos == -1) {
        printf("El numero no existe.\n");
        return N;
    }

    for (i = pos; i < N - 1; i++) {
        VEC[i] = VEC[i + 1];
    }

    return N - 1;
}

void mostrar(int VEC[], int N) {
    int i;

    printf("Arreglo: ");

    for (i = 0; i < N; i++) {
        printf("%d ", VEC[i]);
    }

    printf("\n");
}

int main(void) {
    int VEC[100];
    int N, i, ELE, opcion;

    printf("Cantidad de elementos (1-100): ");
    scanf("%d", &N);

    if (N < 1 || N > 100) {
        printf("Cantidad invalida.\n");
        return 0;
    }

    printf("Introduce los numeros en orden creciente:\n");

    for (i = 0; i < N; i++) {
        scanf("%d", &VEC[i]);
    }

    mostrar(VEC, N);

    printf("1. Insertar numero\n");
    printf("2. Eliminar numero\n");
    printf("Elige una opcion: ");
    scanf("%d", &opcion);

    printf("Introduce el numero: ");
    scanf("%d", &ELE);

    if (opcion == 1) {
        N = insertar(VEC, N, ELE);
    } else if (opcion == 2) {
        N = eliminar(VEC, N, ELE);
    } else {
        printf("Opcion invalida.\n");
        return 0;
    }

    mostrar(VEC, N);

    return 0;
}
