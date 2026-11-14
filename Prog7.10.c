
#include <stdio.h>
#include <string.h>

int main() {
    char fecha[11];
    char cad[50];
    char respuesta;
    int longitud;

    printf("Introduce la fecha de hoy (dd/mm/aaaa): ");
    fgets(fecha, sizeof(fecha), stdin);

    longitud = strlen(fecha);

    if (longitud > 0 && fecha[longitud - 1] == '\n') {
        fecha[longitud - 1] = '\0';
    }

    do {
        printf("Desea ingresar una cadena? (S/N): ");
        scanf(" %c", &respuesta);
        getchar();

        if (respuesta == 'S' || respuesta == 's') {
            printf("Introduce una cadena: ");
            fgets(cad, sizeof(cad), stdin);

            longitud = strlen(cad);

            if (longitud > 0 && cad[longitud - 1] == '\n') {
                cad[longitud - 1] = '\0';
            }

            if (strncmp(cad, fecha, 10) == 0) {
                printf("Cadena encontrada: %s\n", cad);
            }
        }

    } while (respuesta == 'S' || respuesta == 's');

    return 0;
}
