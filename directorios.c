#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

//#define _POSIX_SOURCE

typedef struct {
    int cant_lineas;
    int cant_letras;
    char nombre[100];
    char tipo[15];
} InfoLinea;

int main(){
    int tamano = 12;
    int contador = 0;
    InfoLinea * lista_general = malloc (tamano * sizeof(InfoLinea)); //Arreglo dinamico

    if (lista_general == NULL){
        perror("Error al alocar memoria para la lista");
        return 1;
    }


    DIR * directory;
    struct dirent * entry;

    directory = opendir(".");


    if (directory == NULL){
        printf("Error al abrir la carpeta\n");
        return 1;
    }

    while ((entry = readdir(directory)) != NULL){
        
        //Segun una documentacion, si d_type es 8, significa que estas hablando de un archivo, no un directorio
        if (entry->d_type == 8 && strstr(entry->d_name,".txt") !=NULL && strcmp(entry->d_name + strlen(entry->d_name)-4,".txt") == 0 && strcmp(entry->d_name, "README.txt") != 0){
            printf("File: %s\n", entry->d_name);
            strcpy(lista_general[contador].nombre,entry->d_name);
            contador++;
            //Ahora de paso crearemos un arreglo dinamico del tamaño exacto a los casos donde el archivo termina en txt
        }
        
    }

    if (closedir(directory) == -1){
        printf("Error al cerrar el archivo\n");
        return 1;
    }

    printf("Hasta aqui todo bien \n");

    for (int i = 0; i < contador; i++){

        printf("nombre del archivo es: %s\n", lista_general[i].nombre);
        
    }

    free(lista_general);

    return 0;
}