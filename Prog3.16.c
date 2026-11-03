
#include <stdio.h>

int main(void) {
    int n, i, num;
    int positivos = 0, negativos = 0, nulos = 0;

    printf("Cuantos numeros va a ingresar? ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Debe ingresar una cantidad positiva.\n");
        return 0;
    }

    for (i = 1; i <= n; i++) {
        printf("Ingrese el numero %d: ", i);
        scanf("%d", &num);

        if (num > 0) {
            positivos++;
        } else if (num < 0) {
            negativos++;
        } else {
            nulos++;
        }
    }

    printf("\nPositivos: %d\n", positivos);
    printf("Negativos: %d\n", negativos);
    printf("Nulos: %d\n", nulos);

    return 0;
}
