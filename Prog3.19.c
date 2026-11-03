
#include <stdio.h>
#include <math.h>

int main(void) {
    int n, i;
    double termino, suma = 0;

    printf("Ingrese el numero de terminos: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Debe ingresar un numero positivo.\n");
        return 0;
    }

    for (i = 1; i <= n; i++) {
        termino = pow(i, i);

        if (i % 2 == 0) {
            suma = suma - termino;
        } else {
            suma = suma + termino;
        }
    }

    printf("El resultado de la serie es: %.0f\n", suma);

    return 0;
}
