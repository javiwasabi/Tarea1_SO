#include <stdio.h>
#include "algoritmo.h"

int main() {
    const char *nombre_archivo = "casa.txt";
    InfoLinea result = contador_general(nombre_archivo);
    
    if (result.cant_lineas > 0) {
        printf("Tipo de Resolucion: %s\n", result.tipo);
        printf("Nombre del archivo: %s\n", result.nombre);
        printf("Numero de lineas: %d\n", result.cant_lineas);
        printf("Letras por linea: %d\n", result.cant_letras); //Duplicar numero en caso de contar espacios
    }
    
    horizontal(&result);

    printf("Hasta aqui se ejecuta lo inicial \n");

    printf("Ahora lo de la matriz\n");

    //matriz('perro.txt');
    //printf("\n");
    //int i = horizontal_aux(result.nombre, "CASA");
    return 0;
}
