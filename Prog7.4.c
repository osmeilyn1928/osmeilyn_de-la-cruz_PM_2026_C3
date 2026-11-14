
#include <stdio.h>
#include <string.h>

int main() {
    char cad[30];
    char resultado[50];
    char meses[12][12] = {
        "Enero", "Febrero", "Marzo", "Abril",
        "Mayo", "Junio", "Julio", "Agosto",
        "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };

    int dia, mes, anio;

    printf("Introduce una fecha (dd/mm/aa): ");
    fgets(cad, sizeof(cad), stdin);

    if (sscanf(cad, "%d/%d/%d", &dia, &mes, &anio) != 3) {
        printf("Formato de fecha incorrecto.\n");
        return 1;
    }

    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 ||
        anio < 0 || anio > 99) {
        printf("Fecha incorrecta.\n");
        return 1;
    }

    anio += 2000;

    sprintf(resultado, "%02d de %s de %04d",
            dia, meses[mes - 1], anio);

    printf("Nueva fecha: %s\n", resultado);

    return 0;
}
