#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "torneo.h"



void ingresarResultadosManualmente() {
    FILE *archivo_equipos = fopen("equipos.txt", "r");
    FILE *archivo_resultados = fopen("resultados.txt", "w");
    if (archivo_equipos == NULL || archivo_resultados == NULL) {
        printf("No se ha podido abrir los archivos de equipos.txt o resultados.txt\n");
        exit(1);
    }

    char equipo1[100], equipo2[100];
    int goles_equipo1, goles_equipo2;

    rewind(archivo_equipos);
    while (fscanf(archivo_equipos, "%s", equipo1) != EOF) {
        FILE *temp = fopen("equipos.txt", "r");
        if (temp == NULL) {
            printf("Error al abrir el archivo equipos.txt\n");
            exit(1);
        }

        while (fscanf(temp, "%s", equipo2) != EOF) {
            if (strcmp(equipo1, equipo2) != 0) {
                printf("Ingrese los goles para el partido entre %s y %s: ", equipo1, equipo2);
                scanf("%d %d", &goles_equipo1, &goles_equipo2);

                fprintf(archivo_resultados, "%s %s %d %d\n", equipo1, equipo2, goles_equipo1, goles_equipo2);
            }
        }

        fclose(temp);
    }

    fclose(archivo_equipos);
    fclose(archivo_resultados);
}

void generarResultadosAleatorios() {
    FILE *archivo_equipos = fopen("equipos.txt", "r");
    FILE *archivo_resultados = fopen("resultados.txt", "w");
    if (archivo_equipos == NULL || archivo_resultados == NULL) {
        printf("Error al abrir los archivos equipos.txt o resultados.txt\n");
        exit(1);
    }

    char equipo1[100], equipo2[100];
    int goles_equipo1, goles_equipo2;

    rewind(archivo_equipos);
    while (fscanf(archivo_equipos, "%s", equipo1) != EOF) {
        FILE *temp = fopen("equipos.txt", "r");
        if (temp == NULL) {
            printf("Error al abrir el archivo equipos.txt\n");
            exit(1);
        }

        while (fscanf(temp, "%s", equipo2) != EOF) {
            if (strcmp(equipo1, equipo2) != 0) {
                goles_equipo1 = rand() % 5;  // Generar un número aleatorio entre 0 y 4
                goles_equipo2 = rand() % 5;  // Generar un número aleatorio entre 0 y 4

                fprintf(archivo_resultados, "%s %s %d %d\n", equipo1, equipo2, goles_equipo1, goles_equipo2);
            }
        }

        fclose(temp);
    }

    fclose(archivo_equipos);
    fclose(archivo_resultados);
}


int elegirOpcionResultados() {
    int opcion;

    printf("Seleccione como desea obtener los resultados de los encuentros:\n");
    printf("1) Ingresar resultados manualmente\n");
    printf("2) Generar resultados aleatoriamente\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);

    return opcion;
}
