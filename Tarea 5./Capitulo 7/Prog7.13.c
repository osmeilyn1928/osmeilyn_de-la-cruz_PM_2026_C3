
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char ARC[10][50];
    int i, j;
    int palabras, dentroPalabra;

    for (i = 0; i < 10; i++) {
        printf("Introduce la cadena %d: ", i + 1);
        fgets(ARC[i], sizeof(ARC[i]), stdin);

        int longitud = strlen(ARC[i]);

        if (longitud > 0 && ARC[i][longitud - 1] == '\n') {
            ARC[i][longitud - 1] = '\0';
        }
    }

    printf("\nCantidad de palabras por cadena:\n");

    for (i = 0; i < 10; i++) {
        palabras = 0;
        dentroPalabra = 0;

        for (j = 0; ARC[i][j] != '\0'; j++) {
            if (isspace((unsigned char)ARC[i][j])) {
                dentroPalabra = 0;
            } else if (dentroPalabra == 0) {
                palabras++;
                dentroPalabra = 1;
            }
        }

        printf("Cadena %d: %d palabras\n", i + 1, palabras);
    }

    return 0;
}
