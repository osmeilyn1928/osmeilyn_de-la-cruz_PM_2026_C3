
#include <stdio.h>

#define MAX 1000

struct Producto {
    int clave;
    char nombre[50];
    int existencia;
    float precio;
};

struct Producto productos[MAX];
int n = 0;

/* Cargar los productos del archivo */
void cargar(void) {
    FILE *archivo;
    archivo = fopen("com.dat", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir com.dat\n");
        return;
    }

    n = 0;

    while (n < MAX &&
           fscanf(archivo, "%d %49s %d %f",
                  &productos[n].clave,
                  productos[n].nombre,
                  &productos[n].existencia,
                  &productos[n].precio) == 4) {
        n++;
    }

    fclose(archivo);
}

/* Guardar los cambios en el archivo */
void guardar(void) {
    FILE *archivo;
    int i;

    archivo = fopen("com.dat", "w");

    if (archivo == NULL) {
        printf("No se pudo guardar el inventario\n");
        return;
    }

    for (i = 0; i < n; i++) {
        fprintf(archivo, "%d %s %d %.2f\n",
                productos[i].clave,
                productos[i].nombre,
                productos[i].existencia,
                productos[i].precio);
    }

    fclose(archivo);
}

/* Buscar un producto por su clave */
int buscar(int clave) {
    int i;

    for (i = 0; i < n; i++) {
        if (productos[i].clave == clave) {
            return i;
        }
    }

    return -1;
}

/* a) Ventas */
void ventas(void) {
    int clave, cantidad, pos;
    float total = 0;

    printf("\n--- VENTAS ---\n");

    do {
        printf("Clave del producto (0 para terminar): ");
        scanf("%d", &clave);

        if (clave == 0) {
            break;
        }

        pos = buscar(clave);

        if (pos == -1) {
            printf("Producto no encontrado.\n");
        } else {
            printf("Cantidad a vender: ");
            scanf("%d", &cantidad);

            if (cantidad <= 0) {
                printf("La cantidad debe ser positiva.\n");
            } else if (cantidad > productos[pos].existencia) {
                printf("No hay suficiente existencia.\n");
            } else {
                productos[pos].existencia -= cantidad;
                total += cantidad * productos[pos].precio;

                printf("Producto agregado a la venta.\n");
            }
        }

    } while (clave != 0);

    guardar();
    printf("Total de la venta: RD$ %.2f\n", total);
}

/* b) Reabastecimiento */
void reabastecimiento(void) {
    int clave, cantidad, pos;

    printf("\n--- REABASTECIMIENTO ---\n");

    do {
        printf("Clave del producto (0 para terminar): ");
        scanf("%d", &clave);

        if (clave == 0) {
            break;
        }

        pos = buscar(clave);

        if (pos == -1) {
            printf("Producto no encontrado.\n");
        } else {
            printf("Cantidad que se agregara: ");
            scanf("%d", &cantidad);

            if (cantidad > 0 &&
                cantidad <= 2147483647 - productos[pos].existencia) {
                productos[pos].existencia += cantidad;
                printf("Existencia actualizada.\n");
            } else {
                printf("Cantidad no valida.\n");
            }
        }

    } while (clave != 0);

    guardar();
}

/* c) Agregar nuevos productos */
void nuevosProductos(void) {
    struct Producto nuevo;
    int i, pos;

    printf("\n--- NUEVOS PRODUCTOS ---\n");

    do {
        printf("Clave del producto (0 para terminar): ");
        scanf("%d", &nuevo.clave);

        if (nuevo.clave == 0) {
            break;
        }

        if (nuevo.clave < 0 || buscar(nuevo.clave) != -1) {
            printf("Clave invalida o ya existente.\n");
            continue;
        }

        if (n >= MAX) {
            printf("El inventario esta lleno.\n");
            break;
        }

        printf("Nombre (sin espacios): ");
        scanf("%49s", nuevo.nombre);

        printf("Existencia inicial: ");
        scanf("%d", &nuevo.existencia);

        printf("Precio unitario: ");
        scanf("%f", &nuevo.precio);

        if (nuevo.existencia < 0 || nuevo.precio < 0) {
            printf("Existencia o precio no validos.\n");
            continue;
        }

        pos = 0;

        while (pos < n &&
               productos[pos].clave < nuevo.clave) {
            pos++;
        }

        for (i = n; i > pos; i--) {
            productos[i] = productos[i - 1];
        }

        productos[pos] = nuevo;
        n++;

        printf("Producto agregado correctamente.\n");

    } while (nuevo.clave != 0);

    guardar();
}

/* d) Mostrar el inventario */
void inventario(void) {
    int i;

    printf("\n--- INVENTARIO COMPLETO ---\n");
    printf("Clave  Nombre  Existencia  Precio\n");

    for (i = 0; i < n; i++) {
        printf("%d  %s  %d  RD$ %.2f\n",
               productos[i].clave,
               productos[i].nombre,
               productos[i].existencia,
               productos[i].precio);
    }
}

int main(void) {
    int opcion;

    cargar();

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Ventas\n");
        printf("2. Reabastecimiento\n");
        printf("3. Nuevos productos\n");
        printf("4. Inventario\n");
        printf("0. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                ventas();
                break;

            case 2:
                reabastecimiento();
                break;

            case 3:
                nuevosProductos();
                break;

            case 4:
                inventario();
                break;

            case 0:
                printf("Programa finalizado.\n");
                break;

            default:
                printf("Opcion no valida.\n");
        }

    } while (opcion != 0);

    return 0;
}
