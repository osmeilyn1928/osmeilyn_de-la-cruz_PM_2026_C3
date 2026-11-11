
#include <stdio.h>

void fibonacci(int VEC[], int N) {
    int i;

    VEC[0] = 0;
    VEC[1] = 1;

    for (i = 2; i < N; i++) {
        VEC[i] = VEC[i - 1] + VEC[i - 2];
    }
}

int main(void) {
    int VEC[100];
    int i;

    fibonacci(VEC, 100);

    printf("Numeros de Fibonacci:\n");

    for (i = 0; i < 100; i++) {
        printf("%d ", VEC[i]);
    }

    printf("\n");

    return 0;
}
