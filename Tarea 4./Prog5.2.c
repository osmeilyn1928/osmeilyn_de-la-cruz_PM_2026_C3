
#include <stdio.h>

int eliminarRepetidos(int VEC[], int N) {
    int i, j;

    if (N == 0) {
        return 0;
    }

    j = 0;

    for (i = 1; i < N; i++) {
        if (VEC[i] != VEC[j]) {
            j++;
            VEC[j] = VEC[i];
        }
    }

    return j + 1;
}

int main(void) {
    int VEC[100];
    int N, i, cantidad;

    printf("Cuantos numeros vas a ingresar (1-100): ");
    scanf("%d", &N);

    if (N < 1 || N > 100) {
        printf("La cantidad debe estar entre 1 y 100.\n");
        return 1;
    }

    for (i = 0; i < N; i++) {
        printf("Ingresa el numero %d: ", i + 1);
        scanf("%d", &VEC[i]);
    }

    cantidad = eliminarRepetidos(VEC, N);

    printf("Arreglo sin repetidos: ");

    for (i = 0; i < cantidad; i++) {
        printf("%d ", VEC[i]);
    }

    printf("\n");

    return 0;
}
