
#include <stdio.h>

#define CENTROS 10
#define MESES 12
#define ANOS 5

int main() {
    int SEC[CENTROS][MESES][ANOS];
    int totales[CENTROS] = {0};
    int visitantesMes[MESES] = {0};

    char *meses[MESES] = {
        "Enero", "Febrero", "Marzo", "Abril",
        "Mayo", "Junio", "Julio", "Agosto",
        "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };

    int i, j, k;
    int mayorCentro = 0, menorCentro = 0;
    int mayorMes = 0, menorMes = 0;

    /* Leer los datos de visitantes */
    printf("DATOS DE VISITANTES TURISTICOS\n");

    for (i = 0; i < CENTROS; i++) {
        printf("\n--- Centro turistico %d ---\n", i + 1);

        for (j = 0; j < MESES; j++) {
            for (k = 0; k < ANOS; k++) {
                printf("%s, ano %d: ", meses[j], k + 1);
                scanf("%d", &SEC[i][j][k]);

                totales[i] += SEC[i][j][k];
            }
        }
    }

    /* Calcular los visitantes por mes durante el ultimo ano */
    for (j = 0; j < MESES; j++) {
        for (i = 0; i < CENTROS; i++) {
            visitantesMes[j] += SEC[i][j][ANOS - 1];
        }
    }

    /* Encontrar el centro mas y menos visitado */
    for (i = 1; i < CENTROS; i++) {
        if (totales[i] > totales[mayorCentro]) {
            mayorCentro = i;
        }

        if (totales[i] < totales[menorCentro]) {
            menorCentro = i;
        }
    }

    /* Encontrar el mes con mayor y menor afluencia */
    for (j = 1; j < MESES; j++) {
        if (visitantesMes[j] > visitantesMes[mayorMes]) {
            mayorMes = j;
        }

        if (visitantesMes[j] < visitantesMes[menorMes]) {
            menorMes = j;
        }
    }

    /* Mostrar resultados */
    printf("\n\nTOTAL DE VISITANTES POR CENTRO\n");

    for (i = 0; i < CENTROS; i++) {
        printf("Centro %d: %d visitantes\n",
               i + 1, totales[i]);
    }

    printf("\nCentro mas visitado: Centro %d, con %d visitantes.\n",
           mayorCentro + 1, totales[mayorCentro]);

    printf("Centro menos visitado: Centro %d, con %d visitantes.\n",
           menorCentro + 1, totales[menorCentro]);

    printf("\nAFUENCIA TURISTICA DEL ANO 5\n");

    printf("Mes con mayor afluencia: %s, con %d visitantes.\n",
           meses[mayorMes], visitantesMes[mayorMes]);

    printf("Mes con menor afluencia: %s, con %d visitantes.\n",
           meses[menorMes], visitantesMes[menorMes]);

    return 0;
}
