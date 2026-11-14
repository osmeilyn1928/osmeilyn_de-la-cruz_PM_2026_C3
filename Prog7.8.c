
#include <stdio.h>
#include <string.h>

int main() {
    char cad1[50];
    char cad2[50];
    char *palabra1;
    char *palabra2;
    int primero = 1;

    printf("Introduce la primera cadena: ");
    fgets(cad1, sizeof(cad1), stdin);

    printf("Introduce la segunda cadena: ");
    fgets(cad2, sizeof(cad2), stdin);

    palabra1 = strtok(cad1, " \t\n");
    palabra2 = strtok(cad2, " \t\n");

    printf("Cadena intercalada: ");

    while (palabra1 != NULL || palabra2 != NULL) {

        if (palabra1 != NULL) {
            if (!primero) {
                printf(" ");
            }

            printf("%s", palabra1);
            primero = 0;
            palabra1 = strtok(NULL, " \t\n");
        }

        if (palabra2 != NULL) {
            if (!primero) {
                printf(" ");
            }

            printf("%s", palabra2);
            primero = 0;
            palabra2 = strtok(NULL, " \t\n");
        }
    }

    printf("\n");

    return 0;
}
