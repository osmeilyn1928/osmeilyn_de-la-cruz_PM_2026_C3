
#include <stdio.h>

#define DEP 5
#define MES 12

void leerVentas(float VEN[DEP][MES]) {
    int i, j;

    for (i = 0; i < DEP; i++) {
        printf("\nDepartamento %d:\n", i + 1);

        for (j = 0; j < MES; j++) {
            printf("Ventas del mes %d: ", j + 1);
            scanf("%f", &VEN[i][j]);
        }
    }
}

void ventasMensuales(float VEN[DEP][MES]) {
    int i, j;
    float totalMes, totalAnual = 0;

    printf("\n--- VENTAS MENSUALES ---\n");

    for (j = 0; j < MES; j++) {
        totalMes = 0;

        for (i = 0; i < DEP; i++) {
            totalMes += VEN[i][j];
        }

        printf("Mes %d: %.2f\n", j + 1, totalMes);
        totalAnual += totalMes;
    }

    printf("Total anual de la fabrica: %.2f\n", totalAnual);
}

void mayorVentaJulio(float VEN[DEP][MES]) {
    int i, departamento = 0;
    float mayor = VEN[0][6];

    for (i = 1; i < DEP; i++) {
        if (VEN[i][6] > mayor) {
            mayor = VEN[i][6];
            departamento = i;
        }
    }

    printf("\n--- VENTAS DE JULIO ---\n");
    printf("Departamento con mayor venta: %d\n",
           departamento + 1);
    printf("Monto de la venta: %.2f\n", mayor);
}

void ventasDepartamento3(float VEN[DEP][MES]) {
    int j;
    int mesMayor = 0, mesMenor = 0;
    float mayor = VEN[2][0];
    float menor = VEN[2][0];

    for (j = 1; j < MES; j++) {
        if (VEN[2][j] > mayor) {
            mayor = VEN[2][j];
            mesMayor = j;
        }

        if (VEN[2][j] < menor) {
            menor = VEN[2][j];
            mesMenor = j;
        }
    }

    printf("\n--- DEPARTAMENTO 3 ---\n");
    printf("Mes con mayores ventas: %d\n", mesMayor + 1);
    printf("Monto: %.2f\n", mayor);

    printf("Mes con menores ventas: %d\n", mesMenor + 1);
    printf("Monto: %.2f\n", menor);
}

int main(void) {
    float VEN[DEP][MES];

    leerVentas(VEN);
    ventasMensuales(VEN);
    mayorVentaJulio(VEN);
    ventasDepartamento3(VEN);

    return 0;
}
