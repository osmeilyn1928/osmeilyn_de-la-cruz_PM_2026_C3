
#include <stdio.h>
#include <ctype.h>

int main(void) {
    FILE *archivo;
    int caracter;
    int palabras = 0;
    int dentroPalabra = 0;

    archivo = fopen("arc.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo arc.txt\n");
        return 1;
    }

    while ((caracter = fgetc(archivo)) != EOF) {
        if (isspace((unsigned char)caracter)) {
            dentroPalabra = 0;
        } else {
            if (dentroPalabra == 0) {
                palabras++;
                dentroPalabra = 1;
            }
        }
    }

    fclose(archivo);

    printf("El archivo contiene %d palabras.\n", palabras);

    return 0;
}
