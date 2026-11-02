
#include <stdio.h>

int main(void) {
    int voto;
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;
    int total = 0;

    printf("Ingrese el voto (1 a 5, 0 para terminar): ");
    scanf("%d", &voto);

    while (voto != 0) {
        switch (voto) {
            case 1: c1++; total++; break;
            case 2: c2++; total++; break;
            case 3: c3++; total++; break;
            case 4: c4++; total++; break;
            case 5: c5++; total++; break;
            default:
                printf("Voto no valido. No se cuenta.\n");
        }

        printf("Ingrese otro voto (0 para terminar): ");
        scanf("%d", &voto);
    }

    if (total > 0) {
        printf("\nCandidato 1: %d votos (%.2f%%)\n", c1, c1 * 100.0 / total);
        printf("Candidato 2: %d votos (%.2f%%)\n", c2, c2 * 100.0 / total);
        printf("Candidato 3: %d votos (%.2f%%)\n", c3, c3 * 100.0 / total);
        printf("Candidato 4: %d votos (%.2f%%)\n", c4, c4 * 100.0 / total);
        printf("Candidato 5: %d votos (%.2f%%)\n", c5, c5 * 100.0 / total);
        printf("Total de votos validos: %d\n", total);
    } else {
        printf("No se ingresaron votos validos.\n");
    }

    return 0;
}
