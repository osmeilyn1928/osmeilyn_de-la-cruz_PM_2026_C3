
#include <stdio.h>

int main(void) {
    int numero1, numero2;

    printf("Ingrese el primer numero: ");
    scanf("%d", &numero1);

    printf("Ingrese el segundo numero: ");
    scanf("%d", &numero2);

    if (numero1 > numero2) {
        printf("El primer numero es mayor.\n");
    } else if (numero2 > numero1) {
        printf("El segundo numero es mayor.\n");
    } else {
        printf("Los dos numeros son iguales.\n");
    }

    return 0;
}
```