
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char cad[30];
    int i;

    printf("Introduce un numero telefonico de 10 digitos: ");
    fgets(cad, sizeof(cad), stdin);

    int longitud = strlen(cad);

    if (longitud > 0 && cad[longitud - 1] == '\n') {
        cad[longitud - 1] = '\0';
        longitud--;
    }

    if (longitud != 10) {
        printf("Error: debes ingresar 10 digitos.\n");
        return 1;
    }

    for (i = 0; i < longitud; i++) {
        if (!isdigit((unsigned char)cad[i])) {
            printf("Error: solo debes ingresar numeros.\n");
            return 1;
        }
    }

    printf("Numero telefonico: %s\n", cad);
    printf("Nueva cadena: (%.2s)-%.1s-%.7s\n",
           cad, cad + 2, cad + 3);

    return 0;
}
