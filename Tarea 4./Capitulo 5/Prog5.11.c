
#include <stdio.h>

void buscarPerfectos(int VEC[], int cantidad) {
    int num = 2;
    int encontrados = 0;

    while (encontrados < cantidad) {
        int suma = 1;
        int i;

        for (i = 2; i <= num / 2; i++) {
            if (num % i == 0) {
                suma += i;
            }
        }

        if (suma == num) {
            VEC[encontrados] = num;
            encontrados++;
        }

        num++;
    }
}

int main(void) {
    int VEC[5];
    int i;

    buscarPerfectos(VEC, 5);

    printf("Numeros perfectos encontrados:\n");

    for (i = 0; i < 5; i++) {
        printf("%d\n", VEC[i]);
    }

    return 0;
}
