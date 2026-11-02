
#include <stdio.h>

int main(void) {
    int i = 1, bandera = 0, cantidad = 1;
    double resultado = 4.0 / i;

    while ((3.1415 - resultado > 0.0005) ||
           (resultado - 3.1415 > 0.0005)) {

        i = i + 2;

        if (bandera == 1) {
            resultado = resultado + 4.0 / i;
            bandera = 0;
        } else {
            resultado = resultado - 4.0 / i;
            bandera = 1;
        }

        cantidad++;
    }

    printf("Numero de terminos necesarios: %d\n", cantidad);

    return 0;
}
