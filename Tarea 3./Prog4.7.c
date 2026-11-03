
#include <stdio.h>

int esPrimo(int NUM) {
    int i;

    if (NUM < 2) {
        return 0;
    }

    for (i = 2; i <= NUM / i; i++) {
        if (NUM % i == 0) {
            return 0;
        }
    }

    return 1;
}

int main() {
    int NUM;

    printf("Introduce un numero entero positivo: ");
    scanf("%d", &NUM);

    if (NUM < 1) {
        printf("El numero debe ser positivo.\n");
    } else if (esPrimo(NUM)) {
        printf("%d es primo.\n", NUM);
    } else {
        printf("%d no es primo.\n", NUM);
    }

    return 0;
}
