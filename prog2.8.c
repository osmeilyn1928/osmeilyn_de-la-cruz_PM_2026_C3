#include <stdio.h>
int main(void) {
    int matricula, carrera, semestre;
    float promedio;
    int cumple = 0;
    char nombreCarrera[20];
printf("Ingrese la matricula del estudiante: ");
scanf("%d", &matricula);
printf("Carrera (1-Industrial, 2-Telematica, 3-Computacion, 4-Mecanica): ");
scanf("%d", &carrera);
printf("Ingrese el semestre que cursa: ");
scanf("%d", &semestre);
printf("Ingrese el promedio: ");
scanf("%f", &promedio);
switch (carrera) {
case 1:
sprintf(nombreCarrera, "Industrial");
if (semestre >= 6 && promedio >= 8.5)
 cumple = 1;
break;
 case 2:
sprintf(nombreCarrera, "Telematica");
if (semestre >= 5 && promedio >= 9.0)
cumple = 1;
break;
case 3:
sprintf(nombreCarrera, "Computacion");
if (semestre >= 6 && promedio >= 8.8)
cumple = 1;
break;
case 4:
sprintf(nombreCarrera, "Mecanica");
if (semestre >= 7 && promedio >= 9.0)
cumple = 1;
break;
default:
 printf("El codigo de carrera no es valido.\n");
 return 1;
}
 if (cumple == 1) {
 printf("\nEl estudiante cumple los requisitos.\n");
 printf("Matricula: %d\n", matricula);
  printf("Carrera: %s\n", nombreCarrera);
 printf("Promedio: %.2f\n", promedio);
} else {
printf("\nEl estudiante no cumple los requisitos.\n");
}
return 0;
}