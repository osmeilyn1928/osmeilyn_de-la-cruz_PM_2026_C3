
#include <stdio.h>

int esPerfecto(int N) {
    int i, suma = 0;

    for (i = 1; i <= N / 2; i++) {
        if (N % i == 0) {
            suma = suma + i;
        }
    }

    if (suma == N) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int N, i;

    printf("Introduce un numero entero positivo: ");
    scanf("%d", &N);

    printf("Numeros perfectos entre 1 y %d:\n", N);

    for (i = 2; i <= N; i++) {
        if (esPerfecto(i)) {
            printf("%d\n", i);
        }
    }

    return 0;
}
