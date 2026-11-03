
#include <stdio.h>
#include <math.h>

double calcularInversion(double CAP, double TAS, int MES) {
    return CAP * pow(1 + TAS / 100, MES);
}

int main() {
    double CAP, TAS, resultado;
    int MES;

    printf("Introduce el capital inicial: ");
    scanf("%lf", &CAP);

    printf("Introduce la tasa de interes mensual (%%): ");
    scanf("%lf", &TAS);

    printf("Introduce la cantidad de meses: ");
    scanf("%d", &MES);

    resultado = calcularInversion(CAP, TAS, MES);

    printf("El monto final es: %.2f\n", resultado);

    return 0;
}
