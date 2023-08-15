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

int calculateAsciiDifference(const char *str1, const char *str2) {
    int sum1 = 0, sum2 = 0;

    // Calculate the sum of ASCII values for characters in the first string
    for (int i = 0; i < strlen(str1); i++) {
        sum1 += str1[i];
    }

    // Calculate the sum of ASCII values for characters in the second string
    for (int i = 0; i < strlen(str2); i++) {
        sum2 += str2[i];
    }

    // Return the difference between the two sums
    return sum1 - sum2;
}


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

int moverArchivo(InfoLinea * inf){
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

int c_carpeta(char * buffer, size_t size, InfoLinea * inf){
    char path[256];
    char aux_nom[100];
    char dimension[10];

    subPalabra(inf->cant_letras,inf->cant_lineas,dimension);
    strcpy(aux_nom, inf->nombre);

    //snprintf(path, sizeof(path), "CWD/horizontal/%s/%s", dimension,aux_nom);


    if(getcwd(buffer, size) == NULL){
        perror("getcwd fallo");
        return 1;
    }

    if (chdir("CWD") != 0){
        return 1;
    }

    printf("%s\n", aux_nom);

    if (strstr(inf->tipo, "horizontal") != NULL){

        snprintf(path, sizeof(path), "CWD/horizontal/%s/%s", dimension,aux_nom);
        printf("%s\n", path);

        if (chdir("horizontal") != 0){
            return 1;
        }
        printf("Llego hasta aqui AAAA\n");
        //Para el caso donde esto ocurra, asumiremos que no fue una falla del sistema, si no que la carpeta ya existe
        if (createFolder(dimension) != 0){

            if (rename(aux_nom, path) != 0){
                perror("Error al mover el archivo 1");
                return 1;
            }

            if (chdir(buffer) != 0){
                return 1;
            }

            return 0;
        }

        if (rename(aux_nom, path) != 0){
            perror("Error al mover el archivo 2");
            return 1;
        }

        if (chdir(buffer) != 0){
            return 1;
        }

        return 0;
    } else {
        printf("no corrio xd\n");
    }

    // if (chdir("horizontal") != 0){
    //     return 1;
    // }

    // if (createFolder(path) != 0){

    // }

    // if (chdir(buffer) != 0){
    //     return 1;
    // }
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

    test.cant_letras = 50;
    test.cant_lineas = 50;
    strcpy(test.nombre,"myFile.txt");
    strcpy(test.tipo,"horizontal");

    if (_inicio(cwd, sizeof(cwd)) != 0){
        perror("Error en la funcion '_inicio'");
    }

    if (crearCarpetaEnHori(cwd, sizeof(cwd),"50x50") != 0){
        return 1; 
    }

    if (moverArchivo(&test) != 0){
        return 1;
    }
    // printf("Previa\n");

    // if (c_carpeta(cwd,sizeof(cwd), &test) != 0){
    //     perror("ERROR FATAL");
    // }

    // printf("Corrio la wea,creo\n");
    
    return 0;
}
