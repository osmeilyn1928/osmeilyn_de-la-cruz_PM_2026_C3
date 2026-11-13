
#include <stdio.h>

void mezclar(int VEC1[], int VEC2[], int VEC3[],
             int N, int M) {
    int i;

    for (i = 0; i < N; i++) {
        VEC3[i] = VEC1[i];
    }

    for (i = 0; i < M; i++) {
        VEC3[N + i] = VEC2[i];
    }
}

void ordenar(int VEC[], int T) {
    int i, j, aux;

    for (i = 0; i < T - 1; i++) {
        for (j = 0; j < T - 1 - i; j++) {
            if (VEC[j] < VEC[j + 1]) {
                aux = VEC[j];
                VEC[j] = VEC[j + 1];
                VEC[j + 1] = aux;
            }
        }
    }
}

void mostrar(int VEC[], int T) {
    int i;

    for (i = 0; i < T; i++) {
        printf("%d ", VEC[i]);
    }

    printf("\n");
}

int main(void) {
    int VEC1[100], VEC2[100], VEC3[200];
    int N, M, i;

    printf("Cantidad de elementos del primer arreglo: ");
    scanf("%d", &N);

    if (N < 1 || N > 100) {
        printf("Cantidad invalida.\n");
        return 0;
    }

    for (i = 0; i < N; i++) {
        printf("Elemento %d del primer arreglo: ", i + 1);
        scanf("%d", &VEC1[i]);
    }

    printf("Cantidad de elementos del segundo arreglo: ");
    scanf("%d", &M);

    if (M < 1 || M > 100) {
        printf("Cantidad invalida.\n");
        return 0;
    }

    for (i = 0; i < M; i++) {
        printf("Elemento %d del segundo arreglo: ", i + 1);
        scanf("%d", &VEC2[i]);
    }

    mezclar(VEC1, VEC2, VEC3, N, M);
    ordenar(VEC3, N + M);

    printf("\nArreglo ordenado de mayor a menor:\n");
    mostrar(VEC3, N + M);

    return 0;
}
