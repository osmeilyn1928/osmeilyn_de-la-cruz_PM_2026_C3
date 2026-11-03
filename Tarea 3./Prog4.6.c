
#include <stdio.h>
#include <math.h>

double calcularCoseno(double X, int *cantidad) {
    double suma = 1.0;
    double termino = 1.0;
    double anterior;
    int k = 1;

    do {
        anterior = suma;

        termino = termino * (-X * X) /
                  ((2 * k - 1) * (2 * k));

        suma = suma + termino;
        k++;

    } while (fabs(suma - anterior) > 0.001 && k < 1000);

    *cantidad = k - 1;
    return suma;
}

int main() {
    int X, cantidad;
    double resultado;

    printf("Introduce el valor de X en radianes: ");
    scanf("%d", &X);

    resultado = calcularCoseno(X, &cantidad);

    printf("El coseno aproximado es: %.6f\n", resultado);
    printf("Cantidad de terminos utilizados: %d\n", cantidad);

    return 0;
}
