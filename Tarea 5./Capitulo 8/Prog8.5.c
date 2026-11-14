
#include <stdio.h>
#include <string.h>

typedef struct {
    int clave;
    char nombre[50];
    int existencia;
} Producto;

int main() {
    Producto TIENDA[100];
    char OPE;
    int N, i;
    int CLA, CAN;
    int encontrado;

    printf("Cantidad de productos (1-100): ");
    scanf("%d", &N);

    if (N < 1 || N > 100) {
        printf("Cantidad incorrecta.\n");
        return 1;
    }

    /* Registrar los productos */
    for (i = 0; i < N; i++) {
        printf("\nProducto %d\n", i + 1);

        printf("Clave del producto: ");
        scanf("%d", &TIENDA[i].clave);

        printf("Nombre del producto: ");
        scanf(" %49[^\n]", TIENDA[i].nombre);

        printf("Existencia inicial: ");
        scanf("%d", &TIENDA[i].existencia);

        if (TIENDA[i].existencia < 0) {
            printf("La existencia no puede ser negativa.\n");
            return 1;
        }
    }

    /* Procesar las transacciones */
    printf("\n===== REGISTRO DE TRANSACCIONES =====\n");
    printf("C = Compra, V = Venta\n");
    printf("Para terminar, introduce: 0 0 0\n");

    while (1) {
        printf("\nOperacion (C/V/0): ");
        scanf(" %c", &OPE);

        printf("Clave del producto: ");
        scanf("%d", &CLA);

        printf("Cantidad: ");
        scanf("%d", &CAN);

        if (OPE == '0' && CLA == 0 && CAN == 0) {
            break;
        }

        if (CAN <= 0) {
            printf("La cantidad debe ser mayor que cero.\n");
            continue;
        }

        encontrado = 0;

        for (i = 0; i < N; i++) {
            if (TIENDA[i].clave == CLA) {
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            printf("Producto no encontrado.\n");
            continue;
        }

        if (OPE == 'C' || OPE == 'c') {
            TIENDA[i].existencia += CAN;
            printf("Compra registrada correctamente.\n");
        } else if (OPE == 'V' || OPE == 'v') {
            if (CAN > TIENDA[i].existencia) {
                printf("Venta rechazada: existencias insuficientes.\n");
            } else {
                TIENDA[i].existencia -= CAN;
                printf("Venta registrada correctamente.\n");
            }
        } else {
            printf("Operacion incorrecta. Use C o V.\n");
        }
    }

    /* Mostrar las existencias actualizadas */
    printf("\n===== INVENTARIO ACTUALIZADO =====\n");
    printf("%-10s %-25s %12s\n",
           "Clave", "Producto", "Existencia");

    for (i = 0; i < N; i++) {
        printf("%-10d %-25s %12d\n",
               TIENDA[i].clave,
               TIENDA[i].nombre,
               TIENDA[i].existencia);
    }

    return 0;
}
