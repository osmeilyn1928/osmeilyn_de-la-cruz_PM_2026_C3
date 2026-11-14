
#include <stdio.h>
#include <string.h>

int main() {
    char cad[31];
    int i, longitud;

    printf("Introduce una cadena: ");
    fgets(cad, sizeof(cad), stdin);

    longitud = strlen(cad);

    if (longitud > 0 && cad[longitud - 1] == '\n') {
        cad[longitud - 1] = '\0';
        longitud--;
    }

    for (i = longitud; i < 30; i++) {
        cad[i] = '-';
    }

    cad[30] = '\0';

    printf("Cadena completa: %s\n", cad);

    return 0;
}
