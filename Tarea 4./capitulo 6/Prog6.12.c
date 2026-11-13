
#include <stdio.h>

#define ESTADIOS 7
#define MESES 12
#define ANOS 5

int main() {
    int FUT[ESTADIOS][MESES][ANOS];
    int totalCincoAnos[ESTADIOS] = {0};
    int totalUltimoAno[ESTADIOS] = {0};
    int orden[ESTADIOS];

    char *meses[MESES] = {
        "Enero", "Febrero", "Marzo", "Abril",
        "Mayo", "Junio", "Julio", "Agosto",
        "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };

    int i, j, k, aux;
    int mayorEstadio = 0, menorEstadio = 0;
    int mayorMes;

    /* Leer los datos */
    printf("DATOS DE ASISTENCIA A LOS ESTADIOS\n");

    for (i = 0; i < ESTADIOS; i++) {
        printf("\n--- Estadio %d ---\n", i + 1);

        for (j = 0; j < MESES; j++) {
            for (k = 0; k < ANOS; k++) {
                printf("%s, ano %d: ", meses[j], k + 1);
                scanf("%d", &FUT[i][j][k]);

                totalCincoAnos[i] += FUT[i][j][k];

                if (k == ANOS - 1) {
                    totalUltimoAno[i] += FUT[i][j][k];
                }
            }
        }

        orden[i] = i;
    }

    /* Ordenar los estadios por asistencia del ultimo ano */
    for (i = 0; i < ESTADIOS - 1; i++) {
        for (j = 0; j < ESTADIOS - 1 - i; j++) {
            if (totalUltimoAno[orden[j]] <
                totalUltimoAno[orden[j + 1]]) {

                aux = orden[j];
                orden[j] = orden[j + 1];
                orden[j + 1] = aux;
            }
        }
    }

    /* Buscar el estadio mas y menos concurrido en cinco anos */
    for (i = 1; i < ESTADIOS; i++) {
        if (totalCincoAnos[i] > totalCincoAnos[mayorEstadio]) {
            mayorEstadio = i;
        }

        if (totalCincoAnos[i] < totalCincoAnos[menorEstadio]) {
            menorEstadio = i;
        }
    }

    /* Mostrar asistencia del ultimo ano, de mayor a menor */
    printf("\nASISTENCIA DEL ULTIMO ANO\n");

    for (i = 0; i < ESTADIOS; i++) {
        printf("Estadio %d: %d asistentes\n",
               orden[i] + 1, totalUltimoAno[orden[i]]);
    }

    /* Mostrar los estadios extremos de los cinco anos */
    printf("\nASISTENCIA ACUMULADA EN CINCO ANOS\n");

    printf("Estadio con mayor asistencia: %d, con %d asistentes.\n",
           mayorEstadio + 1, totalCincoAnos[mayorEstadio]);

    printf("Estadio con menor asistencia: %d, con %d asistentes.\n",
           menorEstadio + 1, totalCincoAnos[menorEstadio]);

    /* Buscar el mes de mayor asistencia de cada estadio en el ano 5 */
    printf("\nMES DE MAYOR ASISTENCIA POR ESTADIO EN EL ULTIMO ANO\n");

    for (i = 0; i < ESTADIOS; i++) {
        mayorMes = 0;

        for (j = 1; j < MESES; j++) {
            if (FUT[i][j][ANOS - 1] >
                FUT[i][mayorMes][ANOS - 1]) {
                mayorMes = j;
            }
        }

        printf("Estadio %d: %s, con %d asistentes.\n",
               i + 1, meses[mayorMes],
               FUT[i][mayorMes][ANOS - 1]);
    }

    return 0;
}
