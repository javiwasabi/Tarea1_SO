#include "algoritmo.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

InfoLinea contador_general(const char *nombre_archivo) {
    InfoLinea info = {0, 0, ""};
    
    if (strlen(nombre_archivo) < 100) {
        strcpy(info.nombre, nombre_archivo);
    } else {
        perror("Nombre del archivo es demasiado grande");
        return info;
    }

    FILE *fPointer = fopen(nombre_archivo, "r");
    
    if (fPointer) {
        char tamano[1000];
        
        if (fgets(info.tipo, sizeof(info.tipo), fPointer) != NULL) {
            info.tipo[strcspn(info.tipo, "\n")] = '\0';
        } else {
            perror("Error al leer la primera linea");
        }
        
        if (fgets(tamano, sizeof(tamano), fPointer) != NULL) {
            info.cant_lineas = 1;
            for (int i = 0; tamano[i] != '\0'; i++) {
                if (isalpha(tamano[i])) { // Chequea si el caracter es una letra
                    info.cant_letras++;
                }
            }
        } else {
            perror("Error al leer la segunda linea");
        }
        
        while (fgets(tamano, sizeof(tamano), fPointer) != NULL) {
            info.cant_lineas++;
        }
        
        fclose(fPointer);
    } else {
        perror("Error al leer el archivo");
    }
    
    return info;
}

void horizontal(InfoLinea * infosuck) {
    FILE * file = fopen(infosuck->nombre,"r");
    if (file){
        char linea[1000];
        while (fgets(linea, sizeof(linea),file) != NULL){
            char nlinea[1000];
            int minicont = 0;

            for (int i = 0; linea[i] != '\0'; i++){
                if (!isspace(linea[i])){
                    nlinea[minicont] = linea[i];
                    minicont++;
                }
            }

            nlinea[minicont] = '\0';
            if (horizontal_aux(infosuck->nombre,nlinea) == 1){
                printf("Felicitaciones, se ha encontrado la palabra\n");
                break;
            }
        }

        fclose(file);

    } else {
        perror("Error al abrir el archivo");
    }
}

int horizontal_aux(char * nombre, char * str){
    size_t len = strlen(nombre);
    if (len >= 4){
        nombre[len - 4] = '\0';
    } else {
        perror("El nombre del archivo es demasiado corto");
    }

    for (int i = 0; nombre[i] != '\0'; i++){
        nombre[i] = toupper(nombre[i]);
    }

    char * resultado = strstr(str,nombre);

    if (resultado != NULL){
        //printf("Se hace hecho un match\n");
        return 1;
    } else {
        //printf("No se ha encontrado la palabra\n");
        return 0;
    }
}
/*
char matriz(char * nombre_archivo){

    InfoLinea inf = contador_general(nombre_archivo);

    char confirnom[100] = inf.nombre;
    char Matrix[inf.cant_letras][inf.cant_lineas];

    FILE *fPointer = fopen(nombre_archivo, "r");
    int fila = 0;

    while (!feof(fPointer)){

        for(int i = 0; i < inf.cant_lineas; i++){


           if(fscanf(fPointer, "%c", &Matrix[fila][i]) == EOF){
                break;
            }else{
                if(fPointer != " "){
                    fscanf(fPointer, "%c", &Matrix[fila][i]);
                };
            }; 
        };

        fila++;

        if (fila == inf.cant_letras){
            break;
        }
    };

    fclose(fPointer);

    for(int i = 0; i< inf.cant_letras; i++){
        for(int j= 0; j< inf.cant_lineas; j++){
            printf("%c", Matrix[i][j]);
        }
        printf('\n');

    };

}

void vertical(char nom[], const char nomb){

    char matrixx = matriz(nomb);
    InfoLinea inff = contador_general(nomb);
    bool flag = true;
    char *p = &nom[0];

    for (int c = 0; c< inff.cant_lineas; c++){

        char *p = &nom[0];

        for ( int f= 0; f< inff.cant_letras; f++){

            if(p == matrixx[&c][&f] ){
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

}

*/