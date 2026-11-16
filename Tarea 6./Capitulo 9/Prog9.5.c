#include <stdio.h>
#include <string.h>

int main(void) {
    FILE *archivo;
    FILE *nuevo;
    char lineas[1000][500];
    int cantidad = 0;
    int i;

    archivo = fopen("arc.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo arc.txt\n");
        return 1;
    }

    while (cantidad < 1000 &&
           fgets(lineas[cantidad], sizeof(lineas[cantidad]), archivo) != NULL) {
        cantidad++;
    }

    fclose(archivo);

    nuevo = fopen("arc_invertido.txt", "w");

    if (nuevo == NULL) {
        printf("No se pudo crear arc_invertido.txt\n");
        return 1;
    }

    for (i = cantidad - 1; i >= 0; i--) {
        fputs(lineas[i], nuevo);

        if (strchr(lineas[i], '\n') == NULL) {
            fputc('\n', nuevo);
        }
    }

    fclose(nuevo);

    printf("Se creo el archivo arc_invertido.txt correctamente.\n");

    return 0;
}
