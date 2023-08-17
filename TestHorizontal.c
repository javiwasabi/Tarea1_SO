#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


//#include "algoritmo.h"

typedef struct {
    int cant_lineas;
    int cant_letras;
    char nombre[100];
    char tipo[15];
} InfoLinea;

void horizontal_2(InfoLinea * inf){

    char auxNom[20];
    strcpy(auxNom, inf->nombre);

    size_t tamano = strlen(auxNom);
    
    if (tamano > 4 && strcmp(auxNom + tamano - 4, ".txt") == 0){
        auxNom[tamano -4] = '\0';
    }

    for (size_t i = 0; i < tamano; i++) {
        auxNom[i] = toupper(auxNom[i]);
    }

    
    printf("El nombre del archivo es: %s , y luego queda en %s\n", inf->nombre, auxNom);

    bool flag = false;

    FILE * file = fopen(inf->nombre, "r");
    if (file){
        char linea[1000];
        while (fgets(linea, sizeof(linea), file) != NULL){
            char nlinea[1000];
            int minicont = 0;

            for (int i = 0; linea[i] != '\0'; i++){
                if (!isspace(linea[i])){
                    nlinea[minicont] = linea[i];
                    minicont++;
                }
            }

            nlinea[minicont] = '\0';
            
            char * resultado = strstr(nlinea,auxNom);

            if (resultado != NULL){
                printf("Se ha hecho un match\n");
                flag = true;
            }
        }

        if (flag == false){
            printf("No se ha hecho un match\n");
        }
        fclose(file);
        printf("Archivo cerrado correctamente\n");
    }

}


int main(){
    InfoLinea inff;
    inff.cant_letras=50;
    inff.cant_lineas=50;
    
    strcpy(inff.tipo, "horizontal");
    strcpy(inff.nombre, "perro.txt");

    horizontal_2(&inff);

    
    return 0;
}