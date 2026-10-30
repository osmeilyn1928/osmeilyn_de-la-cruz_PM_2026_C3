
#include <stdio.h>

int main(void) {
    int primero = 0, segundo = 1, siguiente, i;

    printf("Serie de Fibonacci:\n");
    printf("%d\n%d\n", primero, segundo);

    for (i = 3; i <= 50; i++) {
        siguiente = primero + segundo;
        printf("%d\n", siguiente);

        primero = segundo;
        segundo = siguiente;
    }

    return 0;
}
