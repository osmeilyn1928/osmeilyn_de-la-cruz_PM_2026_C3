#include <stdio.h>

int main(void) {
    int num;
    long cuadrado, suma = 0;

    printf("Ingrese un numero (0 para terminar): ");
    scanf("%d", &num);

    while (num != 0) {
        cuadrado = (long)num * num;

        printf("El cuadrado de %d es %ld\n", num, cuadrado);

        suma = suma + cuadrado;

        printf("Ingrese otro numero (0 para terminar): ");
        scanf("%d", &num);
    }

    printf("\nLa suma de los cuadrados es: %ld\n", suma);

    return 0;
}