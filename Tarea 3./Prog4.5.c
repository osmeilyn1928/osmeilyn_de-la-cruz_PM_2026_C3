
#include <stdio.h>

long long potencia(int base, int exponente) {
    long long resultado = 1;
    int i;

    for (i = 1; i <= exponente; i++) {
        resultado = resultado * base;
    }

    return resultado;
}

int main() {
    int N, i;
    long long suma = 0;
    long long termino;

    printf("Introduce el numero de terminos: ");
    scanf("%d", &N);

    if (N < 1 || N > 10) {
        printf("Introduce un numero entre 1 y 10.\n");
        return 1;
    }

    for (i = 1; i <= N; i++) {
        termino = potencia(i, i);

        if (i % 2 == 1) {
            suma = suma + termino;
        } else {
            suma = suma - termino;
        }
    }

    printf("El resultado de la serie es: %lld\n", suma);

    return 0;
}
