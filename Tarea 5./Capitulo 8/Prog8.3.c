
#include <stdio.h>
#include <string.h>

typedef struct {
    int numero;
    char nombre[80];
    char departamento[30];
    char puesto[40];
    char grado[40];
    char nacionalidad[40];
    double salario[12];
} PROFESOR;

int main() {
    PROFESOR EMPLE[200];

    char departamentos[4][30] = {
        "Economia",
        "Derecho",
        "Computacion",
        "Administracion"
    };

    double totalProfesor;
    double mayorIngreso = -1;
    double totalUniversidad = 0;
    double totalExtranjeros = 0;
    double gastoDepartamento[4] = {0, 0, 0, 0};
    double porcentaje;

    int N, i, j, opcion;
    int posicionMayor = 0;
    int posicionDepartamentoMayor = 0;

    printf("Cantidad de profesores (1-200): ");
    scanf("%d", &N);

    if (N < 1 || N > 200) {
        printf("Cantidad incorrecta.\n");
        return 1;
    }

    /* Registrar los datos de los profesores */
    for (i = 0; i < N; i++) {
        printf("\n===== PROFESOR %d =====\n", i + 1);

        printf("Numero de empleado: ");
        scanf("%d", &EMPLE[i].numero);

        printf("Nombre y apellido: ");
        scanf(" %79[^\n]", EMPLE[i].nombre);

        printf("\nSeleccione el departamento:\n");
        printf("1. Economia\n");
        printf("2. Derecho\n");
        printf("3. Computacion\n");
        printf("4. Administracion\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        if (opcion < 1 || opcion > 4) {
            printf("Departamento incorrecto.\n");
            return 1;
        }

        strcpy(EMPLE[i].departamento,
               departamentos[opcion - 1]);

        printf("Puesto que ocupa: ");
        scanf(" %39[^\n]", EMPLE[i].puesto);

        printf("Grado academico: ");
        scanf(" %39[^\n]", EMPLE[i].grado);

        printf("Nacionalidad: ");
        scanf(" %39[^\n]", EMPLE[i].nacionalidad);

        totalProfesor = 0;

        for (j = 0; j < 12; j++) {
            printf("Salario del mes %d: ", j + 1);
            scanf("%lf", &EMPLE[i].salario[j]);

            if (EMPLE[i].salario[j] < 0) {
                printf("El salario no puede ser negativo.\n");
                return 1;
            }

            totalProfesor += EMPLE[i].salario[j];
        }

        /* Calcular el gasto total de la universidad */
        totalUniversidad += totalProfesor;

        /* Buscar al profesor con mayor ingreso anual */
        if (totalProfesor > mayorIngreso) {
            mayorIngreso = totalProfesor;
            posicionMayor = i;
        }

        /* Sumar el gasto del departamento correspondiente */
        for (j = 0; j < 4; j++) {
            if (strcmp(EMPLE[i].departamento,
                       departamentos[j]) == 0) {
                gastoDepartamento[j] += totalProfesor;
            }
        }

        /* Identificar a los profesores extranjeros */
        if (strcmp(EMPLE[i].nacionalidad, "Colombia") != 0) {
            totalExtranjeros += totalProfesor;
        }
    }

    /* Apartado A */
    printf("\n===== APARTADO A =====\n");
    printf("Profesor que mas gano:\n");
    printf("Nombre: %s\n",
           EMPLE[posicionMayor].nombre);
    printf("Departamento: %s\n",
           EMPLE[posicionMayor].departamento);
    printf("Nacionalidad: %s\n",
           EMPLE[posicionMayor].nacionalidad);
    printf("Ingreso anual: %.2f\n", mayorIngreso);

    /* Apartado B */
    printf("\n===== APARTADO B =====\n");
    printf("Total pagado a extranjeros: %.2f\n",
           totalExtranjeros);

    if (totalUniversidad > 0) {
        porcentaje =
            (totalExtranjeros / totalUniversidad) * 100;

        printf("Gasto total de la universidad: %.2f\n",
               totalUniversidad);
        printf("Porcentaje correspondiente: %.2f%%\n",
               porcentaje);
    } else {
        printf("No hubo gastos en salarios.\n");
    }

    /* Apartado C */
    for (i = 1; i < 4; i++) {
        if (gastoDepartamento[i] >
            gastoDepartamento[posicionDepartamentoMayor]) {
            posicionDepartamentoMayor = i;
        }
    }

    printf("\n===== APARTADO C =====\n");
    printf("Departamento con mayor gasto: %s\n",
           departamentos[posicionDepartamentoMayor]);
    printf("Gasto anual: %.2f\n",
           gastoDepartamento[posicionDepartamentoMayor]);

    return 0;
}
