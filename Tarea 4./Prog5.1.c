
#include <stdio.h>

void contarNumeros(int VEC[], int N) {
    int i;
    int positivos = 0;
    int negativos = 0;
    int nulos = 0;

    for (i = 0; i < N; i++) {
        if (VEC[i] > 0) {
            positivos++;
        } else if (VEC[i] < 0) {
            negativos++;
        } else {
            nulos++;
        }
    }

    printf("Numeros positivos: %d\n", positivos);
    printf("Numeros negativos: %d\n", negativos);
    printf("Numeros nulos: %d\n", nulos);
}

int main(void) {
    int VEC[100];
    int N, i;

    printf("Cuantos numeros vas a ingresar (1-100): ");
    scanf("%d", &N);

    if (N < 1 || N > 100) {
        printf("La cantidad debe estar entre 1 y 100.\n");
        return 1;
    }

    for (i = 0; i < N; i++) {
        printf("Ingresa el numero %d: ", i + 1);
        scanf("%d", &VEC[i]);
    }

    contarNumeros(VEC, N);

    return 0;
}
