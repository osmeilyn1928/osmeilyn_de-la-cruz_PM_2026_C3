
#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *archivo;
    char cad[50];
    char linea[1000];
    int contador = 0;
    int longitud;
    int i;

    printf("Introduce la cadena que deseas buscar: ");
    scanf("%49s", cad);

    archivo = fopen("arc2.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo arc2.txt\n");
        return 1;
    }

    longitud = strlen(cad);

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        for (i = 0; linea[i] != '\0'; i++) {
            if (strncmp(&linea[i], cad, longitud) == 0) {
                contador++;
            }
        }
    }

    fclose(archivo);

    printf("La cadena aparece %d veces.\n", contador);

    return 0;
}
