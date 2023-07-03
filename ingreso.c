#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingreso.h"

void ingresarEquipos() {
    FILE *archivo = fopen("equipos.txt", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo .txt\n");
        exit(1);
    }

    char equipo[100];
    int i=1;
    while (1) {
        printf("Ingrese el nombre del equipo %d: \n",i);
        fgets(equipo, sizeof(equipo), stdin);
        equipo[strcspn(equipo, "\n")] = '\0';

        if (strcmp(equipo, "terminar") == 0 || strcmp(equipo, "Terminar") == 0) {
            break;
        }
        i++;
        fprintf(archivo, "%s\n", equipo);
    }

    fclose(archivo);
}
