#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <matriz.c>

void vertical(char nom[], const char nomb){

    char matrixx = matriz(nomb);
    InfoLinea inff = contador_general(nomb);
    bool flag = true;
    char *p = &nom[0];

    for (int c = 0; c< inff.cant_lineas; c++){

        char *p = &nom[0];

        for ( int f= 0; f< inff.cant_letras; f++){

            if(p == matrixx[c][f] ){
                p++;
            }
            if(p == ""  || *p == NULL){

                printf("Se ha encontrado la palabra con éxito\n");
                flag = false;
            }
    }
    if (flag){
        printf("No se encontró la palabra\n");
        }

    }

};
