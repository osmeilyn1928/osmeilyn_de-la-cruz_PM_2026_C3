
#include <stdio.h>

int main(void) {
    int num, i, j, suma, cantidad = 0;

    printf("Ingrese un numero entero positivo: ");
    scanf("%d", &num);

    if (num < 1) {
        printf("Debe ingresar un numero positivo.\n");
        return 0;
    }

    for (i = 1; i <= num; i++) {
        suma = 0;

        for (j = 1; j <= i / 2; j++) {
            if (i % j == 0) {
                suma = suma + j;
            }
        }

        if (suma == i) {
            printf("%d es un numero perfecto.\n", i);
            cantidad++;
        }
    }

    printf("Entre 1 y %d hay %d numeros perfectos.\n", num, cantidad);

    return 0;
}
