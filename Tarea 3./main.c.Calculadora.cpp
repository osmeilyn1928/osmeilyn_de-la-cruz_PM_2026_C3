
#include <stdio.h>

int main() {
    int opcion;
    double num1, num2, resultado;
    double raiz, aproximacion;
    int i;

    do {
        printf("\n===== CALCULADORA =====\n");
        printf("1. Sumar\n");
        printf("2. Restar\n");
        printf("3. Multiplicar\n");
        printf("4. Dividir\n");
        printf("5. Raiz cuadrada\n");
        printf("6. Elevar al cuadrado\n");
        printf("0. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Introduce el primer numero: ");
                scanf("%lf", &num1);
                printf("Introduce el segundo numero: ");
                scanf("%lf", &num2);

                resultado = num1 + num2;
                printf("Resultado: %.2f\n", resultado);
                break;

            case 2:
                printf("Introduce el primer numero: ");
                scanf("%lf", &num1);
                printf("Introduce el segundo numero: ");
                scanf("%lf", &num2);

                resultado = num1 - num2;
                printf("Resultado: %.2f\n", resultado);
                break;

            case 3:
                printf("Introduce el primer numero: ");
                scanf("%lf", &num1);
                printf("Introduce el segundo numero: ");
                scanf("%lf", &num2);

                resultado = num1 * num2;
                printf("Resultado: %.2f\n", resultado);
                break;

            case 4:
                printf("Introduce el primer numero: ");
                scanf("%lf", &num1);
                printf("Introduce el segundo numero: ");
                scanf("%lf", &num2);

                if (num2 != 0) {
                    resultado = num1 / num2;
                    printf("Resultado: %.2f\n", resultado);
                } else {
                    printf("Error: no se puede dividir entre cero.\n");
                }
                break;

            case 5:
                printf("Introduce un numero: ");
                scanf("%lf", &num1);

                if (num1 < 0) {
                    printf("Error: no existe raiz cuadrada real de un numero negativo.\n");
                } else if (num1 == 0) {
                    printf("Raiz cuadrada: 0.00\n");
                } else {
                    aproximacion = num1;

                    for (i = 0; i < 100; i++) {
                        raiz = 0.5 * (aproximacion + num1 / aproximacion);
                        aproximacion = raiz;
                    }

                    printf("Raiz cuadrada: %.6f\n", raiz);
                }
                break;

            case 6:
                printf("Introduce un numero: ");
                scanf("%lf", &num1);

                resultado = num1 * num1;
                printf("Numero elevado al cuadrado: %.2f\n", resultado);
                break;

            case 0:
                printf("Saliendo de la calculadora...\n");
                break;

            default:
                printf("Opcion no valida. Intenta nuevamente.\n");
        }

    } while (opcion != 0);

    return 0;
}
