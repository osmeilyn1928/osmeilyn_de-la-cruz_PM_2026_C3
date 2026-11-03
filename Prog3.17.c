
#include <stdio.h>

int main(void) {
    int n, i;
    long long producto = 1;

    printf("Ingrese la cantidad de numeros naturales: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Debe ingresar un numero positivo.\n");
        return 0;
    }

    for (i = 1; i <= n; i++) {
        producto = producto * i;
    }

    printf("El producto es: %lld\n", producto);

    return 0;
}
