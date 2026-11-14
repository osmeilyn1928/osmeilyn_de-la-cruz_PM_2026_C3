
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char ARC[20][80];
    int frecuencia[80] = {0};
    int i, j, longitud, dentroPalabra;
    int longitudPalabra;

    for (i = 0; i < 20; i++) {
        printf("Introduce la cadena %d (ENTER para terminar): ", i + 1);

        if (fgets(ARC[i], sizeof(ARC[i]), stdin) == NULL) {
            break;
        }

        longitud = strlen(ARC[i]);

        if (longitud > 0 && ARC[i][longitud - 1] == '\n') {
            ARC[i][longitud - 1] = '\0';
        }

        if (ARC[i][0] == '\0') {
            break;
        }

        j = 0;
        dentroPalabra = 0;
        longitudPalabra = 0;

        while (ARC[i][j] != '\0') {
            if (isspace((unsigned char)ARC[i][j]) ||
                ispunct((unsigned char)ARC[i][j])) {

                if (dentroPalabra && longitudPalabra > 0) {
                    frecuencia[longitudPalabra]++;
                }

                dentroPalabra = 0;
                longitudPalabra = 0;

            } else {
                dentroPalabra = 1;
                longitudPalabra++;
            }

            j++;
        }

        if (dentroPalabra && longitudPalabra > 0) {
            frecuencia[longitudPalabra]++;
        }
    }

    printf("\nLongitud de la palabra    Frecuencia\n");

    for (i = 1; i < 80; i++) {
        if (frecuencia[i] > 0) {
            printf("%10d %20d\n", i, frecuencia[i]);
        }
    }

    return 0;
}