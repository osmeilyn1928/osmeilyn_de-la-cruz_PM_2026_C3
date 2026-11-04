
#include <stdio.h>

int invertirNumero(int NUM) {
    int unidades, decenas, centenas, millares;
    int invertido;

    unidades = NUM % 10;
    decenas = (NUM / 10) % 10;
    centenas = (NUM / 100) % 10;
    millares = NUM / 1000;

    invertido = unidades * 1000 + decenas * 100
                + centenas * 10 + millares;

    return invertido;
}

int main() {
    int NUM;

    printf("Introduce un numero de cuatro cifras: ");
    scanf("%d", &NUM);

    if (NUM < 1000 || NUM > 9999) {
        printf("Debes introducir un numero de cuatro cifras.\n");
    } else {
        printf("Numero invertido: %d\n", invertirNumero(NUM));
    }

    return 0;
}
