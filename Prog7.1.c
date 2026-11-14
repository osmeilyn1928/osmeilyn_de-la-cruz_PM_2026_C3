
#include <stdio.h>
#include <string.h>

int main() {
    char cad[50];
    int i;

    printf("Introduce una cadena: ");
    fgets(cad, sizeof(cad), stdin);

    printf("Caracteres en posiciones impares: ");

    for (i = 0; i < strlen(cad); i++) {
        if (i % 2 == 0 && cad[i] != '\n') {
            printf("%c", cad[i]);
        }
    }

    printf("\n");

    return 0;
}
