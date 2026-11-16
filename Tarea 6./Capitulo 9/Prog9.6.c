
#include <stdio.h>
#include <ctype.h>

int main(void) {
    FILE *archivo;
    char palabra[200];
    int i;
    int error;
    int numeroLinea = 0;

    archivo = fopen("doc.dat", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo doc.dat\n");
        return 1;
    }

    while (fgets(palabra, sizeof(palabra), archivo) != NULL) {
        numeroLinea++;
        error = 0;

        for (i = 0; palabra[i] != '\0'; i++) {
            char actual = tolower((unsigned char)palabra[i]);
            char anterior = '\0';

            if (i > 0) {
                anterior = tolower((unsigned char)palabra[i - 1]);
            }

            if ((actual == 'b' && anterior == 'n') ||
                (actual == 'p' && anterior == 'n') ||
                (actual == 'v' && anterior == 'm')) {
                error = 1;
            }
        }

        if (error == 1) {
            printf("Linea %d: revisar %s", numeroLinea, palabra);
        } else {
            printf("Linea %d: sin errores en las reglas revisadas.\n",
                   numeroLinea);
        }
    }

    fclose(archivo);

    return 0;
}
