#include <stdio.h>

int main(void) {
    int i;
    float salario, nomina = 0;

    for (i = 1; i <= 15; i++) {
        printf("Ingrese el salario del profesor %d: ", i);
        scanf("%f", &salario);

        nomina = nomina + salario;
    }

    printf("\nEl total de la nomina es: %.2f\n", nomina);

    return 0;
}