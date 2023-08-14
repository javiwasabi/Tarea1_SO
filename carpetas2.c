#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct {
    int cant_lineas;
    int cant_letras;
    char nombre[100];
    char tipo[15];
} InfoLinea;

void subPalabra(int num1, int num2, char * resultado){
    char resultado1[100];
    char resultado2[100];

    snprintf(resultado1, sizeof(resultado1), "%d", num1);
    snprintf(resultado2, sizeof(resultado2), "%d", num2);

    snprintf(resultado, strlen(resultado1) + strlen(resultado2) + 4, "%sx%s", resultado1, resultado2);

}

int createFolder(const char *foldername) {
    if (mkdir(foldername,0777) != 0) {
        perror("Error creating folder");
        return 1;
    }

    printf("Folder '%s' created successfully!\n", foldername);

    return 0;
}

int mover_hori(InfoLinea * inf){
    char path[256];
    char aux_nom [100];
    char direc[10];

    subPalabra(inf->cant_letras, inf->cant_lineas, direc);

    strcpy(aux_nom, inf->nombre);

    //printf("El lugar a mover es: CWD/%s/%s\n", "horizontal", aux_nom);
    
    snprintf(path, sizeof(path), "CWD/horizontal/%s/%s", direc,aux_nom);

    if (rename(aux_nom, path) != 0){
        perror("Error al mover el archivo");
        return 1;
    }
    return 0;
}

int moveFileToFolder(const char *filename, const char *destinationFolder) {
    char newFilePath[256]; // Adjust the size as needed
    
    snprintf(newFilePath, sizeof(newFilePath), "%s/%s", destinationFolder, filename);

    if (rename(filename, newFilePath) != 0) {
        perror("Error moving file");
        return 1;
    }

    printf("File '%s' moved successfully to '%s'\n", filename, destinationFolder);

    return 0;
}

int crearCarpetaEnHori(char * buffer, size_t size, char * name){

    if(getcwd(buffer, size) == NULL){
        perror("getcwd fallo");
        return 1;
    }

    if (chdir("CWD") != 0){
        return 1;
    }

    if (chdir("horizontal") != 0){
        return 1;
    }

    if (createFolder(name) != 0){

    }

    if (chdir(buffer) != 0){
        return 1;
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
int main() {
    // Creating a folder
    // if (createFolder("myfolder") != 0) {
    //     return 1;
    // }

    // // Moving a file to the folder
    // if (moveFileToFolder("myFile.txt", "myfolder") != 0) {
    //     return 1;
    // }

    char cwd[1024];

    InfoLinea test;

    test.cant_letras = 50;
    test.cant_lineas = 50;
    strcpy(test.nombre,"myFile.txt");

    if (_inicio(cwd, sizeof(cwd)) != 0){
        perror("Error en la funcion '_inicio'");
    }

    if (crearCarpetaEnHori(cwd, sizeof(cwd),"50x50") != 0){
        return 1; 
    }

    if (mover_hori(&test) != 0){
        return 1;
    }
    
    return 0;
}
