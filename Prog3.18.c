
#include <stdio.h>

int main(void) {
    int n, i, edad, sexo;
    int hombres = 0, mujeres = 0;
    float peso, altura;
    float pesoH = 0, alturaH = 0;
    float pesoM = 0, alturaM = 0;

    printf("Ingrese la cantidad de personas: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Debe ingresar una cantidad positiva.\n");
        return 0;
    }

    for (i = 1; i <= n; i++) {
        printf("\nPersona %d\n", i);

        printf("Ingrese la edad: ");
        scanf("%d", &edad);

        printf("Ingrese el peso en kg: ");
        scanf("%f", &peso);

        printf("Ingrese la altura en metros: ");
        scanf("%f", &altura);

        printf("Sexo (1 = hombre, 0 = mujer): ");
        scanf("%d", &sexo);

        if (edad >= 18) {
            if (sexo == 1) {
                pesoH += peso;
                alturaH += altura;
                hombres++;
            } else if (sexo == 0) {
                pesoM += peso;
                alturaM += altura;
                mujeres++;
            }
        }
    }

    if (hombres > 0) {
        printf("\nPromedio de peso de hombres: %.2f kg\n",
               pesoH / hombres);
        printf("Promedio de altura de hombres: %.2f m\n",
               alturaH / hombres);
    } else {
        printf("\nNo hay hombres mayores de edad.\n");
    }

    if (mujeres > 0) {
        printf("\nPromedio de peso de mujeres: %.2f kg\n",
               pesoM / mujeres);
        printf("Promedio de altura de mujeres: %.2f m\n",
               alturaM / mujeres);
    } else {
        printf("\nNo hay mujeres mayores de edad.\n");
    }

    return 0;
}
