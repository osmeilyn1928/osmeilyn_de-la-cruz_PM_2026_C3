
#include <stdio.h>

int main(void) {
    int op, t;
    float res;

    printf("Ingrese la opcion del calculo (1, 2, 3 o 4): ");
    scanf("%d", &op);

    printf("Ingrese el valor entero de T: ");
    scanf("%d", &t);

    switch (op) {
        case 1:
            res = (float)t / 5;
            break;

        case 2:
            res = t * t;
            break;

        case 3:
        case 4:
            res = 6.0 * t / 2;
            break;

        default:
            res = 1;
            break;
    }

    printf("El resultado es: %.2f\n", res);

    return 0;
}
```
