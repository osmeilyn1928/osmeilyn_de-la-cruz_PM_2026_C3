#include <stdio.h>

int main(void) {
    float pago, suma = 0;

    printf("Ingrese el primer pago (0 para terminar): ");
    scanf("%f", &pago);

    while (pago != 0) {
        suma = suma + pago;

        printf("Ingrese el siguiente pago (0 para terminar): ");
        scanf("%f", &pago);
    }

    printf("\nEl total de pagos del mes es: %.2f\n", suma);

    return 0;
}