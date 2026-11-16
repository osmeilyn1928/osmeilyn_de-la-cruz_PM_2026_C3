
#include <stdio.h>

int main(void) {
    FILE *archivo;
    char cadena[1000];
    int i;
    int longitud;
    int mayor = 0;

    archivo = fopen("arc1.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo arc1.txt\n");
        return 1;
    }

    while (fgets(cadena, sizeof(cadena), archivo) != NULL) {
        i = 0;
        longitud = 0;

        while (cadena[i] != '\0' && cadena[i] != '\n') {
            longitud++;
            i++;
        }

        if (longitud > mayor) {
            mayor = longitud;
        }
    }

    fclose(archivo);

    printf("La longitud de la cadena mas grande es: %d\n", mayor);

    return 0;
}
