#include "algoritmo.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>

InfoLinea * inicial(){
    int tamano = 12;
    int contador = 0;
    InfoLinea * lista_general = malloc (tamano * sizeof(InfoLinea)); //Arreglo dinamico

    if (lista_general == NULL){
        perror("Error al alocar memoria para la lista");
        //return;
    }

    DIR * directory;
    struct dirent * entry;

    directory = opendir(".");


    if (directory == NULL){
        printf("Error al abrir la carpeta\n");
        //return;
    }

    while ((entry = readdir(directory)) != NULL){
        
        //Segun una documentacion, si d_type es 8, significa que estas hablando de un archivo, no un directorio
        if (entry->d_type == 8 && strstr(entry->d_name,".txt") !=NULL && strcmp(entry->d_name + strlen(entry->d_name)-4,".txt") == 0 && strcmp(entry->d_name, "README.txt") != 0){
            //printf("File: %s\n", entry->d_name);
            strcpy(lista_general[contador].nombre,entry->d_name);
            contador++;
            //Ahora de paso crearemos un arreglo dinamico del tamaño exacto a los casos donde el archivo termina en txt
        }
        
    }

    if (closedir(directory) == -1){
        printf("Error al cerrar el archivo\n");
        //return;
    }

    return lista_general;
}

void contador_general2(InfoLinea * inf){
    FILE *fPointer = fopen(inf->nombre, "r");
    
    if (fPointer) {
        char tamano[1000];
        if (fgets(inf->tipo, sizeof(inf->tipo), fPointer) != NULL){
            inf->tipo[strcspn(inf->tipo,"\n")] = '\0';
        } else {
            perror("Error al leer la primera linea");
        }

        if (fgets(tamano, sizeof(tamano), fPointer) != NULL) {
            inf->cant_lineas = 1;
            for (int i = 0; tamano[i] != '\0'; i++){
                if (isalpha(tamano[i])){
                    inf->cant_letras++;
                }
            }
        } else {
            perror("Error al leer la segunda linea, ¿Seguro que el archivo esta correcto?");
        }

        while (fgets(tamano, sizeof(tamano),fPointer)!= NULL){
            inf->cant_lineas++;
        }

        fclose(fPointer);
    } else {
        perror("Error al leer el archivo");
    }

    //printf("EUREKAAAAAA\n");
}

void horizontal(InfoLinea * infosuck) {
    bool flag = false;
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
                flag = true;
                break;
            }
        }

        fclose(file);

    }
    if (flag == false){
        printf("No se ha encontrado la palabra\n");
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


