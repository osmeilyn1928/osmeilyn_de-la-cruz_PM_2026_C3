
#include <stdio.h>

int main(void) {
    int num, i;

    printf("Ingrese un numero entero positivo: ");
    scanf("%d", &num);

    if (num <= 0) {
        printf("Debe ingresar un numero positivo.\n");
        return 0;
    }

    for (i = 1; i <= 10; i++) {
        printf("%d x %d = %d\n", num, i, num * i);
    }

    return 0;
}
