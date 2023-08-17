#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include <string.h>

int main() {

    char cwd[1024]; //Esto para la creacion de carpetas
    int cant_carpetas;

    if (_inicio(cwd, sizeof(cwd)) != 0){
        perror("Error en la funcion '_inicio'");
    }

    InfoLinea * result = inicial(&cant_carpetas);
    for (int i =0 ; i < cant_carpetas; i++){
        contador_general2(&result[i]);
    }

    for (int i = 0; i < cant_carpetas; i++){
        char palabra [200];

        printf("El nombre del archivo es: %s\n", result[i].nombre);
        printf("La orientacion del archivo: %s\n", result[i].tipo);
        printf("La dimension horizontal es: %d\n", result[i].cant_letras);
        printf("La dimension vertical es: %d\n", result[i].cant_lineas);
        
        

        if (strstr(result[i].tipo, "horizontal") != NULL){
            printf("Algoritmo horizontal a la marcha\n");
            //horizontal(&result[i]);
            printf("Logro correr\n");


        }if(strstr(result[i].tipo, "vertical") != NULL){
            vertical(&result[i]);
        }


        subPalabra(result[i].cant_letras,result[i].cant_lineas,palabra);

        if (crearCarpetaDimension(cwd,sizeof(cwd),&result[i]) < 0){
            return 1;
        }

        if (moverArchivo(&result[i]) != 0){
            return 1;
        }


        // if (strstr(result[i].tipo, "horizontal") != NULL){
        //     //horizontal(&result[i]);
            
        //     subPalabra(result[i].cant_letras,result[i].cant_lineas,palabra);

        //     if (crearCarpetaDimension(cwd,sizeof(cwd),&result[i]) < 0){
        //         return 1;
        //     }

        //     if (moverArchivo(&result[i]) != 0){
        //         return 1;
        //     }
            

        // } else {
        //     subPalabra(result[i].cant_letras,result[i].cant_lineas,palabra);

        //     if (crearCarpetaDimension(cwd,sizeof(cwd),&result[i]) < 0){
        //         return 1;
        //     }

        //     if (moverArchivo(&result[i]) != 0){
        //         return 1;
        //     }
        // }

        printf("---------------------------\n");
    }

    
    free(result);
    
    return 0;
}
