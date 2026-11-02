#include <stdio.h>
int main(void) {
    float precio, nuevoPrecio;
#include <stdio.h>
    printf("Ingrese el precio del producto: ");
    scanf("%f", &precio);

    if (precio < 1500) {
        nuevoPrecio = precio * 1.11;
    } else {
        nuevoPrecio = precio * 1.08;
    }

    printf("Nuevo precio del producto: %.2f\n", nuevoPrecio);

    return 0;}