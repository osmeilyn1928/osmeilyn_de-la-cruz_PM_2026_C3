#include <stdio.h>

int main(void) {
    int nivel;
    float salario;

    printf("Ingrese el nivel academico del profesor (1-4): ");
    scanf("%d", &nivel);

    printf("Ingrese el salario del profesor: ");
    scanf("%f", &salario);

    switch (nivel) {
        case 1:
            salario = salario * 1.035;
            break;
        case 2:
            salario = salario * 1.041;
            break;
        case 3:
            salario = salario * 1.048;
            break;
        case 4:
            salario = salario * 1.053;
            break;
        default:
            printf("El nivel ingresado no es valido.\n");
            return 1;
    }

    printf("\nNivel: %d\n", nivel);
    printf("Nuevo salario: %.2f\n", salario);

    return 0;
}