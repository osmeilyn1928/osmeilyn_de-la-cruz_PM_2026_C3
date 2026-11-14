
#include <stdio.h>

typedef struct {
    char calleNumero[60];
    char codigoPostal[15];
    char colonia[40];
    char ciudad[40];
    char telefono[20];
} DOMICILIO;

typedef struct {
    long long cuenta;
    char nombre[60];
    DOMICILIO domicilio;
    double saldo;
} CLIENTE;

int main() {
    CLIENTE CLI[100];
    int N, i, encontrado;
    long long cuenta;
    char operacion, metodo;
    double monto;

    printf("Cantidad de clientes (1-100): ");
    scanf("%d", &N);

    if (N < 1 || N > 100) {
        printf("Cantidad de clientes incorrecta.\n");
        return 1;
    }

    for (i = 0; i < N; i++) {
        printf("\n--- Cliente %d ---\n", i + 1);

        printf("Numero de cuenta: ");
        scanf("%lld", &CLI[i].cuenta);

        printf("Nombre completo: ");
        scanf(" %59[^\n]", CLI[i].nombre);

        printf("Calle y numero: ");
        scanf(" %59[^\n]", CLI[i].domicilio.calleNumero);

        printf("Codigo postal: ");
        scanf(" %14[^\n]", CLI[i].domicilio.codigoPostal);

        printf("Colonia: ");
        scanf(" %39[^\n]", CLI[i].domicilio.colonia);

        printf("Ciudad: ");
        scanf(" %39[^\n]", CLI[i].domicilio.ciudad);

        printf("Telefono: ");
        scanf(" %19[^\n]", CLI[i].domicilio.telefono);

        printf("Saldo inicial: ");
        scanf("%lf", &CLI[i].saldo);

        if (CLI[i].cuenta <= 0 || CLI[i].saldo < 0) {
            printf("Numero de cuenta o saldo incorrecto.\n");
            return 1;
        }

        if (i > 0 && CLI[i].cuenta <= CLI[i - 1].cuenta) {
            printf("Las cuentas deben ingresarse en orden creciente.\n");
            return 1;
        }
    }

    printf("\n=== TRANSACCIONES BANCARIAS ===\n");
    printf("Introduce 0 como numero de cuenta para terminar.\n");

    while (1) {
        printf("\nNumero de cuenta: ");
        scanf("%lld", &cuenta);

        if (cuenta == 0) {
            break;
        }

        encontrado = -1;

        for (i = 0; i < N; i++) {
            if (CLI[i].cuenta == cuenta) {
                encontrado = i;
                break;
            }
        }

        if (encontrado == -1) {
            printf("La cuenta no existe.\n");
            continue;
        }

        printf("D = Deposito, R = Retiro: ");
        scanf(" %c", &operacion);

        if (operacion != 'D' && operacion != 'd' &&
            operacion != 'R' && operacion != 'r') {
            printf("Operacion incorrecta.\n");
            continue;
        }

        printf("Monto: ");
        scanf("%lf", &monto);

        if (monto <= 0) {
            printf("El monto debe ser mayor que cero.\n");
            continue;
        }

        if (operacion == 'D' || operacion == 'd') {
            CLI[encontrado].saldo += monto;

            printf("Deposito realizado correctamente.\n");
        } else {
            printf("C = Cheque, A = Cajero automatico: ");
            scanf(" %c", &metodo);

            if (metodo != 'C' && metodo != 'c' &&
                metodo != 'A' && metodo != 'a') {
                printf("Metodo de retiro incorrecto.\n");
                continue;
            }

            if (CLI[encontrado].saldo >= monto) {
                CLI[encontrado].saldo -= monto;

                printf("Retiro realizado correctamente.\n");
            } else {
                printf("Operacion rechazada: saldo insuficiente.\n");
            }
        }

        printf("Cliente: %s\n", CLI[encontrado].nombre);
        printf("Saldo actual: %.2f\n", CLI[encontrado].saldo);
    }

    printf("\n=== SALDOS FINALES ===\n");

    for (i = 0; i < N; i++) {
        printf("Cuenta: %lld | Cliente: %s | Saldo: %.2f\n",
               CLI[i].cuenta,
               CLI[i].nombre,
               CLI[i].saldo);
    }

    printf("\nFin del programa.\n");

    return 0;
}
