
#include <stdio.h>

int main(void) {
    int n, i;
    double producto = 1.0;

    printf("Ingrese la cantidad de terminos: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Debe ingresar un numero positivo.\n");
        return 0;
    }

    for (i = 1; i <= n; i++) {
        producto = producto * (1.0 / i);
    }

    printf("El resultado de la serie es: %.6f\n", producto);

    return 0;
}
