#include "algoritmo.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

InfoLinea * inicial(int * cont){
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

    *cont = contador;

    return lista_general;
}

void contador_general2(InfoLinea * inf){
    FILE *fPointer = fopen(inf->nombre, "r");
    
    if (fPointer) {
        char tamano[1000];
        if (fgets(inf->tipo, sizeof(inf->tipo), fPointer) != NULL){
            inf->tipo[strcspn(inf->tipo,"\n")] = '\0';
        } else {
            perror("Error al leer la primera linea en:");
            printf("%s\n", inf->nombre);
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

/*FUNCIONES PARA LA CREACION DE CARPETAS*/

void subPalabra(int num1, int num2, char * resultado){
    char resultado1[100];
    char resultado2[100];

    snprintf(resultado1, sizeof(resultado1), "%d", num1);
    snprintf(resultado2, sizeof(resultado2), "%d", num2);

    snprintf(resultado, strlen(resultado1) + strlen(resultado2) + 4, "%sx%s", resultado1, resultado2);

}

int createFolder(const char *foldername) {
    int resultado = mkdir(foldername, 0777);
    if (resultado == 0){
        printf("Folder '%s' created successfully!\n", foldername);
        return 0;
    } else {
        if (errno == EEXIST) {
            fprintf(stderr, "La carpeta '%s' ya existe\n", foldername);
            return 1;
        } else {
            perror("Error en la creacion de archivos\n");
            return -1;
        }
    }
}

int moverArchivo(InfoLinea * inf){
    char path[256];
    char aux_nom [100];
    char direc[10];

    subPalabra(inf->cant_letras, inf->cant_lineas, direc);

    strcpy(aux_nom, inf->nombre);

    //printf("El lugar a mover es: CWD/%s/%s\n", "horizontal", aux_nom);
    if (strcmp(inf->tipo, "horizontal") == 0){
        snprintf(path, sizeof(path), "CWD/horizontal/%s/%s", direc,aux_nom);
        printf("Ahora moveremos el archivo: %s a su destino horizontal\n", aux_nom);
    } else {
        snprintf(path, sizeof(path), "CWD/vertical/%s/%s", direc,aux_nom);
        printf("Ahora moveremos el archivo: %s a su destino vertical\n", aux_nom);
    }
    
    if (rename(aux_nom, path) != 0){
        perror("Error al mover el archivo");
        return 1;
    }
    return 0;
}

int crearCarpetaDimension(char * buffer, size_t size, InfoLinea * inf) {
    
    char resultado[15];
    subPalabra(inf->cant_letras,inf->cant_lineas,resultado);
    
    if(getcwd(buffer, size) == NULL){
        perror("getcwd fallo");
        return 1;
    }

    if (chdir("CWD") != 0){
        return 1;
    }

    if (strcmp(inf->tipo, "horizontal") == 0){
        
        if (chdir("horizontal") != 0){
            return 1;
        }

        //ESta lina es especifico para el nombre "50x50";
        if (createFolder(resultado) != 0){

        }

        if (chdir(buffer) != 0){
            return 1;
        }
    } else {

        if (chdir("vertical") != 0){
            return 1;
        }

        //ESta lina es especifico para el nombre "50x50";
        if (createFolder(resultado) != 0){

        }

        if (chdir(buffer) != 0){
            return 1;
        }
        
    }
}


int _inicio(char * buffer, size_t size){
    
    if(getcwd(buffer, size) == NULL){
        perror("getcwd fallo");
        return 1;
    }

    if (createFolder("CWD") != 0){
        return 1;
    }
    if (chdir("CWD") != 0){
        return 1;
    }
    if (createFolder("vertical") != 0){
        return 1;
    }
    if (createFolder("horizontal") != 0){
        return 1;
    }

    if(chdir(buffer) != 0){
        return 1;
    }
}
