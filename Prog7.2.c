
#include <stdio.h>
#include <string.h>

int main() {
    char cad[50];
    int i;

    printf("Introduce una cadena: ");
    fgets(cad, sizeof(cad), stdin);

    printf("Digitos en posiciones pares: ");

    for (i = 0; i < strlen(cad); i++) {
        if (i % 2 == 1 &&
            cad[i] >= '0' &&
            cad[i] <= '9') {
            printf("%c", cad[i]);
        }
    }

    printf("\n");

    return 0;
}
