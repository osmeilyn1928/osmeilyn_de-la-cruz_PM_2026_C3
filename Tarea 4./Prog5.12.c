
#include <stdio.h>

int esPalindromo(int VEC[], int N) {
    int i;

    for (i = 0; i < N / 2; i++) {
        if (VEC[i] != VEC[N - 1 - i]) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    int VEC[100];
    int N, i;

    printf("Cantidad de elementos del arreglo: ");
    scanf("%d", &N);

    if (N < 1 || N > 100) {
        printf("Cantidad invalida.\n");
        return 0;
    }

    for (i = 0; i < N; i++) {
        printf("Introduce el elemento %d: ", i + 1);
        scanf("%d", &VEC[i]);
    }

    if (esPalindromo(VEC, N)) {
        printf("El arreglo es palindromo.\n");
    } else {
        printf("El arreglo no es palindromo.\n");
    }

    return 0;
}
