#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include <string.h>

int main() {

    InfoLinea * result = inicial();
    for (int i =0 ; i < 4; i++){
        contador_general2(&result[i]);
    }

    for (int i = 0; i < 4; i++){
        printf("El nombre del archivo es: %s\n", result[i].nombre);
        printf("La orientacion del archivo: %s\n", result[i].tipo);
        printf("La dimension horizontal es: %d\n", result[i].cant_letras);
        printf("La dimension vertical es: %d\n", result[i].cant_lineas);
    }

    if (strstr(result[0].tipo, "horizontal") != NULL){
        printf("EUREKA\n");
    }
    free(result);
    
    return 0;
}
