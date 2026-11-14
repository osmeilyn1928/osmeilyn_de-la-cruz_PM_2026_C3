
#include <stdio.h>
#include <string.h>

#define MAX 1000
#define MATERIAS 7

typedef struct {
    char calleNumero[60];
    int codigoPostal;
    char colonia[40];
    char ciudad[40];
    char telefono[20];
} DOMICILIO;

typedef struct {
    char materia[40];
    double promedio;
} CALIFICACION;

typedef struct {
    char nivel[20];
    int grado;
    char salon[20];
    CALIFICACION calificaciones[MATERIAS];
} NIVEL_ESTUDIOS;

typedef struct {
    int matricula;
    char nombre[80];
    DOMICILIO domicilio;
    NIVEL_ESTUDIOS estudios;
} ALUMNO;

void limpiarBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void leerCadena(char cadena[], int tamano) {
    fgets(cadena, tamano, stdin);
    cadena[strcspn(cadena, "\n")] = '\0';
}

double calcularPromedio(ALUMNO alumno) {
    double suma = 0;
    int i;

    for (i = 0; i < MATERIAS; i++) {
        suma += alumno.estudios.calificaciones[i].promedio;
    }

    return suma / MATERIAS;
}

int perteneceGrupo(ALUMNO alumno, char nivel[],
                   int grado, char salon[]) {
    return strcmp(alumno.estudios.nivel, nivel) == 0 &&
           alumno.estudios.grado == grado &&
           strcmp(alumno.estudios.salon, salon) == 0;
}

int main(void) {
    ALUMNO ESCUELA[MAX];
    int N, i, j;
    int opcion;
    int matriculaBuscada;
    int encontrado;
    int gradoBuscado;
    int hayAlumnos;
    int posicionMayor;
    double promedio;

    printf("Cantidad de alumnos (1-1000): ");
    scanf("%d", &N);
    limpiarBuffer();

    if (N < 1 || N > MAX) {
        printf("Cantidad de alumnos incorrecta.\n");
        return 1;
    }

    /* Registrar los datos de cada alumno */
    for (i = 0; i < N; i++) {
        printf("\n========== ALUMNO %d ==========\n", i + 1);

        printf("Matricula: ");
        scanf("%d", &ESCUELA[i].matricula);
        limpiarBuffer();

        printf("Nombre y apellido: ");
        leerCadena(ESCUELA[i].nombre,
                   sizeof(ESCUELA[i].nombre));

        printf("Calle y numero: ");
        leerCadena(ESCUELA[i].domicilio.calleNumero,
                   sizeof(ESCUELA[i].domicilio.calleNumero));

        printf("Codigo postal: ");
        scanf("%d", &ESCUELA[i].domicilio.codigoPostal);
        limpiarBuffer();

        printf("Colonia: ");
        leerCadena(ESCUELA[i].domicilio.colonia,
                   sizeof(ESCUELA[i].domicilio.colonia));

        printf("Ciudad: ");
        leerCadena(ESCUELA[i].domicilio.ciudad,
                   sizeof(ESCUELA[i].domicilio.ciudad));

        printf("Telefono: ");
        leerCadena(ESCUELA[i].domicilio.telefono,
                   sizeof(ESCUELA[i].domicilio.telefono));

        printf("Nivel (primaria, secundaria o preparatoria): ");
        leerCadena(ESCUELA[i].estudios.nivel,
                   sizeof(ESCUELA[i].estudios.nivel));

        printf("Grado: ");
        scanf("%d", &ESCUELA[i].estudios.grado);
        limpiarBuffer();

        printf("Salon: ");
        leerCadena(ESCUELA[i].estudios.salon,
                   sizeof(ESCUELA[i].estudios.salon));

        for (j = 0; j < MATERIAS; j++) {
            printf("\nMateria %d: ", j + 1);
            leerCadena(
                ESCUELA[i].estudios.calificaciones[j].materia,
                sizeof(ESCUELA[i].estudios.calificaciones[j].materia)
            );

            printf("Promedio de la materia: ");
            scanf("%lf",
                  &ESCUELA[i].estudios.calificaciones[j].promedio);
            limpiarBuffer();
        }
    }

    /* Menu de operaciones */
    do {
        printf("\n========== MENU ==========\n");
        printf("1. Consultar promedio por matricula\n");
        printf("2. Listar alumnos de un grupo\n");
        printf("3. Alumno con mayor promedio de un grupo\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");

        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case 1:
                printf("Matricula del alumno: ");
                scanf("%d", &matriculaBuscada);
                limpiarBuffer();

                encontrado = 0;

                for (i = 0; i < N; i++) {
                    if (ESCUELA[i].matricula == matriculaBuscada) {
                        promedio = calcularPromedio(ESCUELA[i]);

                        printf("\nNombre: %s\n",
                               ESCUELA[i].nombre);
                        printf("Promedio general: %.2f\n",
                               promedio);

                        encontrado = 1;
                        break;
                    }
                }

                if (!encontrado) {
                    printf("Matricula no encontrada.\n");
                }
                break;

            case 2: {
                char nivelBuscado[20];
                char salonBuscado[20];

                printf("Nivel de estudios: ");
                leerCadena(nivelBuscado, sizeof(nivelBuscado));

                printf("Grado: ");
                scanf("%d", &gradoBuscado);
                limpiarBuffer();

                printf("Salon: ");
                leerCadena(salonBuscado, sizeof(salonBuscado));

                hayAlumnos = 0;

                printf("\n%-12s %-30s %10s\n",
                       "Matricula", "Nombre", "Promedio");

                for (i = 0; i < N; i++) {
                    if (perteneceGrupo(ESCUELA[i],
                                       nivelBuscado,
                                       gradoBuscado,
                                       salonBuscado)) {
                        printf("%-12d %-30s %10.2f\n",
                               ESCUELA[i].matricula,
                               ESCUELA[i].nombre,
                               calcularPromedio(ESCUELA[i]));

                        hayAlumnos = 1;
                    }
                }

                if (!hayAlumnos) {
                    printf("No hay alumnos en ese grupo.\n");
                }
                break;
            }

            case 3: {
                char nivelBuscado[20];
                char salonBuscado[20];

                printf("Nivel de estudios: ");
                leerCadena(nivelBuscado, sizeof(nivelBuscado));

                printf("Grado: ");
                scanf("%d", &gradoBuscado);
                limpiarBuffer();

                printf("Salon: ");
                leerCadena(salonBuscado, sizeof(salonBuscado));

                posicionMayor = -1;

                for (i = 0; i < N; i++) {
                    if (perteneceGrupo(ESCUELA[i],
                                       nivelBuscado,
                                       gradoBuscado,
                                       salonBuscado)) {
                        if (posicionMayor == -1 ||
                            calcularPromedio(ESCUELA[i]) >
                            calcularPromedio(ESCUELA[posicionMayor])) {
                            posicionMayor = i;
                        }
                    }
                }

                if (posicionMayor == -1) {
                    printf("No hay alumnos en ese grupo.\n");
                } else {
                    printf("\nAlumno con mayor promedio:\n");
                    printf("Matricula: %d\n",
                           ESCUELA[posicionMayor].matricula);
                    printf("Nombre: %s\n",
                           ESCUELA[posicionMayor].nombre);
                    printf("Promedio: %.2f\n",
                           calcularPromedio(ESCUELA[posicionMayor]));
                }
                break;
            }

            case 0:
                printf("Programa terminado.\n");
                break;

            default:
                printf("Opcion incorrecta.\n");
        }

    } while (opcion != 0);

    return 0;
}

