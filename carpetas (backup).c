#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

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
    } else {
        snprintf(path, sizeof(path), "CWD/vertical/%s/%s", direc,aux_nom);
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
    //ESta lina es especifico para el nombre "50x50";
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
    
    char cwd[1024];

    InfoLinea test;
    InfoLinea test1;

    test.cant_letras = 50;
    test.cant_lineas = 50;
    strcpy(test.nombre,"myFile.txt");
    strcpy(test.tipo,"horizontal");

    test1.cant_letras = 50;
    test1.cant_lineas = 50;
    strcpy(test1.nombre,"myFile1.txt");
    strcpy(test1.tipo,"vertical");

    char palabra [200];
    subPalabra(test.cant_letras,test.cant_lineas,palabra);

    if (_inicio(cwd, sizeof(cwd)) != 0){
        perror("Error en la funcion '_inicio'");
    }


    if (crearCarpetaDimension(cwd,sizeof(cwd),&test) != 0){
        return 1;
    }

    if (moverArchivo(&test) != 0){
        return 1;
    }

    if (crearCarpetaDimension(cwd,sizeof(cwd),&test1) != 0){
        return 1;
    }

    if (moverArchivo(&test1) != 0){
        return 1;
    }
    
    
    return 0;
}
