
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char cad[50];
    int i;

    printf("Introduce una cadena: ");
    fgets(cad, sizeof(cad), stdin);

    if (cad[0] != '\0' && cad[0] != '\n') {
        cad[0] = toupper((unsigned char)cad[0]);
    }

    for (i = 1; cad[i] != '\0'; i++) {
        if (cad[i - 1] == ' ' && cad[i] != '\n') {
            cad[i] = toupper((unsigned char)cad[i]);
        }
    }

    printf("Cadena modificada: %s", cad);

    return 0;
}
