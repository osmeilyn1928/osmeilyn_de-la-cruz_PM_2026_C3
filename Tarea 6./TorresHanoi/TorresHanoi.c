
#include <stdio.h>

void hanoi(int n, char origen, char auxiliar, char destino) {
    if (n == 1) {
        printf("Mover disco de %c a %c\n", origen, destino);
    } else {
        hanoi(n - 1, origen, destino, auxiliar);

        printf("Mover disco de %c a %c\n", origen, destino);

        hanoi(n - 1, auxiliar, origen, destino);
    }
}

int main(void) {
    int discos;

    printf("TORRES DE HANOI\n");
    printf("Ingrese la cantidad de discos: ");
    scanf("%d", &discos);

    if (discos < 1 || discos > 20) {
        printf("Ingrese un numero entre 1 y 20.\n");
        return 1;
    }

    printf("\nMovimientos necesarios:\n");

    hanoi(discos, 'A', 'B', 'C');

    return 0;
}
