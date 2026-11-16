
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *archivo;
    char *texto;
    char *temporal;
    int caracter;
    size_t longitud = 0;
    size_t capacidad = 10;

    archivo = fopen("texto.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    texto = malloc(capacidad * sizeof(char));

    if (texto == NULL) {
        printf("No se pudo reservar memoria.\n");
        fclose(archivo);
        return 1;
    }

    while ((caracter = fgetc(archivo)) != EOF) {

        if (longitud + 1 >= capacidad) {
            capacidad = capacidad * 2;

            temporal = realloc(texto,
                               capacidad * sizeof(char));

            if (temporal == NULL) {
                printf("No se pudo ampliar la memoria.\n");
                free(texto);
                fclose(archivo);
                return 1;
            }

            texto = temporal;
        }

        texto[longitud] = (char)caracter;
        longitud++;
    }

    texto[longitud] = '\0';

    fclose(archivo);

    printf("Contenido del archivo:\n\n");
    printf("%s\n", texto);

    printf("\nCantidad de caracteres: %zu\n", longitud);

    free(texto);

    return 0;
}
