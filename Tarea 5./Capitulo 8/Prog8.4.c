
#include <stdio.h>
#include <string.h>

typedef struct {
    char calleNumero[60];
    char colonia[40];
    char codigoPostal[15];
    char ciudad[40];
    char telefono[20];
} DOMICILIO;

typedef struct {
    int numero;
    char nombre[80];
    char departamento[40];
    DOMICILIO domicilio;
    double salario;
} EMPLEADO;

int main() {
    EMPLEADO EMPLE[100], nuevo, aux;
    int N = 0;
    int opcion, numero, i, j;
    int encontrado;

    do {
        printf("\n===== MENU DE EMPLEADOS =====\n");
        printf("1. Alta de empleado\n");
        printf("2. Baja de empleado\n");
        printf("3. Listado por departamento\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {

            case 1:
                if (N == 100) {
                    printf("No se pueden agregar mas empleados.\n");
                    break;
                }

                printf("\nNumero de empleado: ");
                scanf("%d", &nuevo.numero);

                encontrado = 0;

                for (i = 0; i < N; i++) {
                    if (EMPLE[i].numero == nuevo.numero) {
                        encontrado = 1;
                        break;
                    }
                }

                if (encontrado) {
                    printf("Ese numero de empleado ya existe.\n");
                    break;
                }

                printf("Nombre y apellido: ");
                scanf(" %79[^\n]", nuevo.nombre);

                printf("Departamento: ");
                scanf(" %39[^\n]", nuevo.departamento);

                printf("Calle y numero: ");
                scanf(" %59[^\n]", nuevo.domicilio.calleNumero);

                printf("Colonia: ");
                scanf(" %39[^\n]", nuevo.domicilio.colonia);

                printf("Codigo postal: ");
                scanf(" %14[^\n]", nuevo.domicilio.codigoPostal);

                printf("Ciudad: ");
                scanf(" %39[^\n]", nuevo.domicilio.ciudad);

                printf("Telefono: ");
                scanf(" %19[^\n]", nuevo.domicilio.telefono);

                printf("Salario mensual: ");
                scanf("%lf", &nuevo.salario);

                if (nuevo.salario < 0) {
                    printf("El salario no puede ser negativo.\n");
                    break;
                }

                /* Buscar la posicion correcta */
                i = 0;

                while (i < N &&
                       EMPLE[i].numero < nuevo.numero) {
                    i++;
                }

                /* Desplazar empleados hacia la derecha */
                for (j = N; j > i; j--) {
                    EMPLE[j] = EMPLE[j - 1];
                }

                EMPLE[i] = nuevo;
                N++;

                printf("Empleado agregado correctamente.\n");
                break;

            case 2:
                printf("\nNumero del empleado que desea eliminar: ");
                scanf("%d", &numero);

                encontrado = 0;

                for (i = 0; i < N; i++) {
                    if (EMPLE[i].numero == numero) {
                        encontrado = 1;
                        break;
                    }
                }

                if (encontrado) {
                    /* Desplazar los empleados hacia la izquierda */
                    for (j = i; j < N - 1; j++) {
                        EMPLE[j] = EMPLE[j + 1];
                    }

                    N--;

                    printf("Empleado eliminado correctamente.\n");
                } else {
                    printf("No se encontro ese empleado.\n");
                }

                break;

            case 3: {
                char departamento[40];

                printf("\nNombre del departamento: ");
                scanf(" %39[^\n]", departamento);

                encontrado = 0;

                printf("\n===== LISTADO DE EMPLEADOS =====\n");
                printf("%-12s %-25s %12s\n",
                       "Numero", "Nombre", "Salario");

                for (i = 0; i < N; i++) {
                    if (strcmp(EMPLE[i].departamento,
                               departamento) == 0) {

                        printf("%-12d %-25s %12.2f\n",
                               EMPLE[i].numero,
                               EMPLE[i].nombre,
                               EMPLE[i].salario);

                        encontrado = 1;
                    }
                }

                if (!encontrado) {
                    printf("No hay empleados en ese departamento.\n");
                }

                break;
            }

            case 4:
                printf("Programa finalizado.\n");
                break;

            default:
                printf("Opcion incorrecta. Intente de nuevo.\n");
        }

    } while (opcion != 4);

    return 0;
}
