
#include <stdio.h>
#include <string.h>

int main() {
    char cad[50];
    char *palabras[25];
    char *palabra;
    int cantidad = 0;
    int i;

    printf("Introduce una cadena: ");
    fgets(cad, sizeof(cad), stdin);

    palabra = strtok(cad, " \t\n");

    while (palabra != NULL && cantidad < 25) {
        palabras[cantidad] = palabra;
        cantidad++;
        palabra = strtok(NULL, " \t\n");
    }

    printf("Cadena inversa: ");

    for (i = cantidad - 1; i >= 0; i--) {
        printf("%s", palabras[i]);

        if (i > 0) {
            printf(" ");
        }
    }

    printf("\n");

    return 0;
}
