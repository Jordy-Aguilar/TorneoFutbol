#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "resultados.h"

typedef struct {
    char equipo[100];
    int puntos;
} Equipo;

int compararEquipos(const void *a, const void *b) {
    const Equipo *equipoA = (const Equipo *)a;
    const Equipo *equipoB = (const Equipo *)b;

    return equipoB->puntos - equipoA->puntos;
}

void calcularPuntos() {
    FILE *archivo_equipos = fopen("equipos.txt", "r");
    FILE *archivo_resultados = fopen("resultados.txt", "r");
    if (archivo_equipos == NULL || archivo_resultados == NULL) {
        printf("No se pudo abrir los archivos de equipos.txt o resultados.txt\n");
        exit(1);
    }

    Equipo equipos[100];
    int num_equipos = 0;

    char equipo[100];
    while (fscanf(archivo_equipos, "%s", equipo) != EOF) {
        strcpy(equipos[num_equipos].equipo, equipo);
        equipos[num_equipos].puntos = 0;
        num_equipos++;
    }

    rewind(archivo_resultados);
    char equipo1[100];
    char equipo2[100];
    int goles_equipo1;
    int goles_equipo2;

    while (fscanf(archivo_resultados, "%s %s %d %d", equipo1, equipo2, &goles_equipo1,
                &goles_equipo2) != EOF) {
        for (int i = 0; i < num_equipos; i++) {
            if (strcmp(equipo1, equipos[i].equipo) == 0) {
                if (goles_equipo1 > goles_equipo2) {
                    equipos[i].puntos += 3;
                } else if (goles_equipo1 == goles_equipo2) {
                    equipos[i].puntos += 1;
                }
            } else if (strcmp(equipo2, equipos[i].equipo) == 0) {
                if (goles_equipo2 > goles_equipo1) {
                    equipos[i].puntos += 3;
                } else if (goles_equipo2 == goles_equipo1) {
                    equipos[i].puntos += 1;
                }
            }
        }
    }

    fclose(archivo_equipos);
    fclose(archivo_resultados);

    qsort(equipos, num_equipos, sizeof(Equipo), compararEquipos);

    FILE *archivo_puntos = fopen("puntos.txt", "w");
    if (archivo_puntos == NULL) {
        printf("Error al abrir el archivo puntos.txt\n");
        exit(1);
    }

    for (int i = 0; i < num_equipos; i++) {
        fprintf(archivo_puntos, "%s: %d\n", equipos[i].equipo, equipos[i].puntos);
    }

    fclose(archivo_puntos);
}

void mostrarResultados() {
    FILE *archivo_resultados = fopen("resultados.txt", "r");
    if (archivo_resultados == NULL) {
        printf("Error al abrir el archivo resultados.txt\n");
        exit(1);
    }

    printf("Resultados de los partidos:\n");
    printf("---------------------------------\n");
    char equipo1[100];
    char equipo2[100];
    int goles_equipo1;
    int goles_equipo2;

    while (fscanf(archivo_resultados, "%s %s %d %d", equipo1, equipo2, &goles_equipo1,
                &goles_equipo2) != EOF) {
        printf("%s %d - %d %s\n", equipo1, goles_equipo1, goles_equipo2, equipo2);
    }

    fclose(archivo_resultados);

    FILE *archivo_puntos = fopen("puntos.txt", "r");
    if (archivo_puntos == NULL) {
        printf("Error al abrir el archivo puntos.txt\n");
        exit(1);
    }

    printf("\nTabla de posiciones:\n");
    printf("---------------------------------\n");
    char equipo[100];
    int puntos;
    int posicion = 1;
    while (fscanf(archivo_puntos, "%s %d", equipo, &puntos) != EOF) {
        printf("%d) %s: %d puntos\n", posicion, equipo, puntos);
        posicion++;
    }

    fclose(archivo_puntos);
}
