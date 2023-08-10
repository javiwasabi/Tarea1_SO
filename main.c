#include <stdio.h>
#include "algoritmo.h"

int main() {
    const char *nombre_archivo = "carro.txt";
    InfoLinea result = contador_general(nombre_archivo);
    
    if (result.cant_lineas > 0) {
        printf("Tipo de Resolucion: %s\n", result.tipo);
        printf("Nombre del archivo: %s\n", result.nombre);
        printf("Numero de lineas: %d\n", result.cant_lineas);
        printf("Letras por linea: %d\n", result.cant_letras); //Duplicar numero en caso de contar espacios
    }
    
    return 0;
}
