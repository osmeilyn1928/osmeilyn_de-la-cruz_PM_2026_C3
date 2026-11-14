
#include <stdio.h>
#include <string.h>

int main() {
    char cad[21];
    char mayor[21] = "";
    char respuesta;
    int longitud;

    do {
        printf("Desea ingresar una cadena? (S/N): ");
        scanf(" %c", &respuesta);
        getchar();

        if (respuesta == 'S' || respuesta == 's') {
            printf("Introduce una cadena (maximo 20 caracteres): ");
            fgets(cad, sizeof(cad), stdin);

            longitud = strlen(cad);

            if (longitud > 0 && cad[longitud - 1] == '\n') {
                cad[longitud - 1] = '\0';
            }

            if (strlen(cad) > strlen(mayor)) {
                strcpy(mayor, cad);
            }
        }

    } while (respuesta == 'S' || respuesta == 's');

    if (strlen(mayor) > 0) {
        printf("La cadena de mayor longitud es: %s\n", mayor);
        printf("Longitud: %lu caracteres\n",
               (unsigned long)strlen(mayor));
    } else {
        printf("No se ingresaron cadenas.\n");
    }

    return 0;
}
