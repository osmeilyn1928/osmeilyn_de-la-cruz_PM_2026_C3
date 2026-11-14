
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char ARC[10][50];
    int i, j;
    int vocales, mayor = -1;
    int posicion = 0;
    char letra;

    for (i = 0; i < 10; i++) {
        printf("Introduce la cadena %d: ", i + 1);
        fgets(ARC[i], sizeof(ARC[i]), stdin);

        int longitud = strlen(ARC[i]);

        if (longitud > 0 && ARC[i][longitud - 1] == '\n') {
            ARC[i][longitud - 1] = '\0';
        }
    }

    for (i = 0; i < 10; i++) {
        vocales = 0;

        for (j = 0; ARC[i][j] != '\0'; j++) {
            letra = tolower((unsigned char)ARC[i][j]);

            if (letra == 'a' || letra == 'e' ||
                letra == 'i' || letra == 'o' ||
                letra == 'u') {
                vocales++;
            }
        }

        if (vocales > mayor) {
            mayor = vocales;
            posicion = i;
        }
    }

    printf("\nLa cadena con mas vocales es: %s\n",
           ARC[posicion]);
    printf("Cantidad de vocales: %d\n", mayor);

    return 0;
}
