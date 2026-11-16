
#include <stdio.h>

int main(void) {
    FILE *archivo;
    int clave, edad, condicion;
    char nombre[50], sexo;
    int total = 0;
    int hombres = 0, mujeres = 0;
    int condiciones[6] = {0};
    int edades[11] = {0};
    int i;

    archivo = fopen("pacientes.dat", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir pacientes.dat\n");
        return 1;
    }

    while (fscanf(archivo, "%d %49s %d %c %d",
                  &clave, nombre, &edad,
                  &sexo, &condicion) == 5) {

        total++;

        if (sexo == 'M' || sexo == 'm') {
            hombres++;
        } else if (sexo == 'F' || sexo == 'f') {
            mujeres++;
        }

        if (condicion >= 1 && condicion <= 5) {
            condiciones[condicion]++;
        }

        if (edad >= 0) {
            if (edad >= 100) {
                edades[10]++;
            } else {
                edades[edad / 10]++;
            }
        }
    }

    fclose(archivo);

    printf("\n--- ESTADISTICAS DEL HOSPITAL ---\n");
    printf("Total de pacientes: %d\n", total);

    if (total > 0) {
        printf("\nPorcentaje de hombres: %.2f%%\n",
               hombres * 100.0 / total);

        printf("Porcentaje de mujeres: %.2f%%\n",
               mujeres * 100.0 / total);
    }

    printf("\n--- PACIENTES POR CONDICION ---\n");

    for (i = 1; i <= 5; i++) {
        printf("Condicion %d: %d pacientes\n",
               i, condiciones[i]);
    }

    printf("\n--- PACIENTES POR EDAD ---\n");

    for (i = 0; i < 10; i++) {
        printf("%d-%d anos: %d pacientes\n",
               i * 10, i * 10 + 9, edades[i]);
    }

    printf("100 anos o mas: %d pacientes\n", edades[10]);

    return 0;
}
