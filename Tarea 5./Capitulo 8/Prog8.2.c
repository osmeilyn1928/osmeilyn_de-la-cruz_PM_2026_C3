
#include <stdio.h>
#include <string.h>

typedef struct {
    char nombre[40];
    int jugados;
    int ganados;
    int empatados;
    int perdidos;
    int golesFavor;
    int golesContra;
    int diferencia;
    int puntos;
} EQUIPO;

int main() {
    EQUIPO FUTBOL[20], aux;
    int N, i;
    int local, visitante;
    int golesLocal, golesVisitante;
    int j;

    printf("Cantidad de equipos (1-20): ");
    scanf("%d", &N);

    if (N < 1 || N > 20) {
        printf("Cantidad incorrecta.\n");
        return 1;
    }

    for (i = 0; i < N; i++) {
        printf("\nNombre del equipo %d: ", i + 1);
        scanf(" %39[^\n]", FUTBOL[i].nombre);

        FUTBOL[i].jugados = 0;
        FUTBOL[i].ganados = 0;
        FUTBOL[i].empatados = 0;
        FUTBOL[i].perdidos = 0;
        FUTBOL[i].golesFavor = 0;
        FUTBOL[i].golesContra = 0;
        FUTBOL[i].diferencia = 0;
        FUTBOL[i].puntos = 0;
    }

    printf("\n=== REGISTRO DE PARTIDOS ===\n");
    printf("Equipos disponibles:\n");

    for (i = 0; i < N; i++) {
        printf("%d. %s\n", i + 1, FUTBOL[i].nombre);
    }

    printf("\nIntroduce el numero del equipo local (0 para terminar).\n");

    while (1) {
        printf("\nEquipo local: ");
        scanf("%d", &local);

        if (local == 0) {
            break;
        }

        printf("Equipo visitante: ");
        scanf("%d", &visitante);

        if (local < 1 || local > N ||
            visitante < 1 || visitante > N ||
            local == visitante) {
            printf("Seleccion de equipos incorrecta.\n");
            continue;
        }

        printf("Goles del equipo local: ");
        scanf("%d", &golesLocal);

        printf("Goles del equipo visitante: ");
        scanf("%d", &golesVisitante);

        if (golesLocal < 0 || golesVisitante < 0) {
            printf("Los goles no pueden ser negativos.\n");
            continue;
        }

        local--;
        visitante--;

        FUTBOL[local].jugados++;
        FUTBOL[visitante].jugados++;

        FUTBOL[local].golesFavor += golesLocal;
        FUTBOL[local].golesContra += golesVisitante;

        FUTBOL[visitante].golesFavor += golesVisitante;
        FUTBOL[visitante].golesContra += golesLocal;

        if (golesLocal > golesVisitante) {
            FUTBOL[local].ganados++;
            FUTBOL[local].puntos += 3;
            FUTBOL[visitante].perdidos++;
        } else if (golesLocal < golesVisitante) {
            FUTBOL[visitante].ganados++;
            FUTBOL[visitante].puntos += 3;
            FUTBOL[local].perdidos++;
        } else {
            FUTBOL[local].empatados++;
            FUTBOL[visitante].empatados++;
            FUTBOL[local].puntos++;
            FUTBOL[visitante].puntos++;
        }
    }

    for (i = 0; i < N; i++) {
        FUTBOL[i].diferencia =
            FUTBOL[i].golesFavor - FUTBOL[i].golesContra;
    }

    /* Ordenar por puntos de mayor a menor */
    for (i = 0; i < N - 1; i++) {
        for (j = 0; j < N - 1 - i; j++) {
            if (FUTBOL[j].puntos < FUTBOL[j + 1].puntos) {
                aux = FUTBOL[j];
                FUTBOL[j] = FUTBOL[j + 1];
                FUTBOL[j + 1] = aux;
            }
        }
    }

    printf("\n========== TABLA DE POSICIONES ==========\n");

    printf("%-20s %3s %3s %3s %3s %3s %3s %4s %3s\n",
           "Equipo", "JJ", "JG", "JE", "JP",
           "GF", "GC", "DG", "PTS");

    for (i = 0; i < N; i++) {
        printf("%-20s %3d %3d %3d %3d %3d %3d %4d %3d\n",
               FUTBOL[i].nombre,
               FUTBOL[i].jugados,
               FUTBOL[i].ganados,
               FUTBOL[i].empatados,
               FUTBOL[i].perdidos,
               FUTBOL[i].golesFavor,
               FUTBOL[i].golesContra,
               FUTBOL[i].diferencia,
               FUTBOL[i].puntos);
    }

    return 0;
}
