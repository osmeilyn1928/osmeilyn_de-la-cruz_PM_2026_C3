
#include <stdio.h>

void combinar(int VEC1[], int VEC2[], int VEC3[],
              int N, int M) {
    int i = 0, j = M - 1, k = 0;

    while (i < N && j >= 0) {
        if (VEC1[i] <= VEC2[j]) {
            VEC3[k] = VEC1[i];
            i++;
        } else {
            VEC3[k] = VEC2[j];
            j--;
        }
        k++;
    }

    while (i < N) {
        VEC3[k] = VEC1[i];
        i++;
        k++;
    }

    while (j >= 0) {
        VEC3[k] = VEC2[j];
        j--;
        k++;
    }
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

    printf("Introduce los numeros de menor a mayor:\n");
    for (i = 0; i < N; i++) {
        scanf("%d", &VEC1[i]);
    }

    printf("Cantidad de elementos del segundo arreglo: ");
    scanf("%d", &M);

    if (M < 1 || M > 100) {
        printf("Cantidad invalida.\n");
        return 0;
    }

    printf("Introduce los numeros de mayor a menor:\n");
    for (i = 0; i < M; i++) {
        scanf("%d", &VEC2[i]);
    }

    combinar(VEC1, VEC2, VEC3, N, M);

    printf("Arreglo combinado de menor a mayor:\n");
    for (i = 0; i < N + M; i++) {
        printf("%d ", VEC3[i]);
    }

    printf("\n");
    return 0;
}
