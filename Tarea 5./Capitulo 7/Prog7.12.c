
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char ARC[10][50];
    int i, j;
    int mayusculas, mayor = -1;
    int posicion = 0;
    int longitud;

    for (i = 0; i < 10; i++) {
        printf("Introduce la cadena %d: ", i + 1);
        fgets(ARC[i], sizeof(ARC[i]), stdin);

        longitud = strlen(ARC[i]);

        if (longitud > 0 && ARC[i][longitud - 1] == '\n') {
            ARC[i][longitud - 1] = '\0';
        }
    }

    for (i = 0; i < 10; i++) {
        mayusculas = 0;

        for (j = 0; ARC[i][j] != '\0'; j++) {
            if (isupper((unsigned char)ARC[i][j])) {
                mayusculas++;
            }
        }

        if (mayusculas > mayor) {
            mayor = mayusculas;
            posicion = i;
        }
    }

    printf("\nLa cadena con mas mayusculas es: %s\n",
           ARC[posicion]);
    printf("Cantidad de mayusculas: %d\n", mayor);

    return 0;
}
