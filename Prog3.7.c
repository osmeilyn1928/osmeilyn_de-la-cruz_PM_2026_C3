#include <stdio.h>

int main(void) {
    int n, i;
    float lanzamiento, suma = 0, promedio;

    do {
        printf("Ingrese la cantidad de lanzamientos (1 a 10): ");
        scanf("%d", &n);
    } while (n < 1 || n > 10);

    for (i = 1; i <= n; i++) {
        printf("Ingrese el lanzamiento %d: ", i);
        scanf("%f", &lanzamiento);
        suma = suma + lanzamiento;
    }

    promedio = suma / n;

    printf("\nEl promedio de los lanzamientos es: %.2f\n", promedio);

    return 0;
}