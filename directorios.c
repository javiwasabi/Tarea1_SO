#include <stdio.h>
#include <dirent.h>
#include <string.h>

//#define _POSIX_SOURCE

int main(){
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
            //Ahora de paso crearemos un arreglo dinamico del tamaño exacto a los casos donde el archivo termina en txt
        }

        //printf("%s\n", entry->d_name);
    }

    if (closedir(directory) == -1){
        printf("Error al cerrar el archivo\n");
        return 1;
    }

    return 0;
}