#include <stdio.h>

int main(void) {
    float pago, suma = 0;

    do {
        printf("Ingrese un pago (0 para terminar): ");
        scanf("%f", &pago);

        suma = suma + pago;

    } while (pago != 0);

    printf("\nEl total de pagos del mes es: %.2f\n", suma);

    return 0;
}