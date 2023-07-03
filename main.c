#include <stdio.h>
#include <stdlib.h>
#include "ingreso.h"
#include "torneo.h"
#include "resultados.h"

int main() {
    ingresarEquipos();

    int opcion = elegirOpcionResultados();
    if (opcion == 1) {
        ingresarResultadosManualmente();
    } else if (opcion == 2) {
        generarResultadosAleatorios();
    } else {
        printf("Usted ingreso una opcion no valida, vuelva a intentarlo\n");
        return 1;
    }

    calcularPuntos();
    mostrarResultados();

    return 0;
}
