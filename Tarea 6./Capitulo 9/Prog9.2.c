
#include <stdio.h>
#include <ctype.h>

int main(void) {
    FILE *archivo;
    int caracter;
    int a = 0, e = 0, i = 0, o = 0, u = 0;

    archivo = fopen("arc.txt", "r");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo arc.txt\n");
        return 1;
    }

    while ((caracter = fgetc(archivo)) != EOF) {
        caracter = tolower((unsigned char)caracter);

        switch (caracter) {
            case 'a':
                a++;
                break;
            case 'e':
                e++;
                break;
            case 'i':
                i++;
                break;
            case 'o':
                o++;
                break;
            case 'u':
                u++;
                break;
        }
    }

    fclose(archivo);

    printf("a: %d\n", a);
    printf("e: %d\n", e);
    printf("i: %d\n", i);
    printf("o: %d\n", o);
    printf("u: %d\n", u);

    return 0;
}
