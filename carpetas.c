#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "algoritmo.h"
#include <string.h>

int crearCarpeta(char * nombre){
    if (mkdir(nombre,0777) != 0){
        perror("Error");
        return 1;
    }
}

int c_inicio(){
    
    if (crearCarpeta("CWD") != 0){
        perror("Error");
        return 1;
    }

    if (chdir("CWD") != 0){
        perror ("Error");
        return 1;
    }

    if (crearCarpeta("vertical") != 0){
        perror("Error");
        return 1;
    }

    if (chdir("vertical") != 0){
        perror ("Error");
        return 1;
    }

    if (crearCarpeta("50x50") != 0){
        return 1;
    }

    if (crearCarpeta("horizontal") != 0){
        perror("Error");
        return 1;
    }
    
    if (chdir("CWD") != 0){
        perror ("Error");
        return 1;
    }




    return 0;
}



void intString (int num, char * resultado){
    snprintf(resultado, sizeof(resultado), "%d", num);
}

void insertar(char * str1, char * str2, char * result){
    snprintf(result,strlen(str1) + strlen(str2) + 4, "%sx%s", str1, str2);
}

void dimee(int num1, int num2, char * resultadof){
    char resultado1[100];
    char resultado2[100];

    intString(num1, resultado1);
    intString(num2, resultado2);

    insertar(resultado1,resultado2,resultadof);

}


int moverArchivoVertical(InfoLinea * inf){
    char path[1024];
    char resultado[100];

    dimee(inf->cant_letras,inf->cant_lineas,resultado);

    snprintf(path,sizeof(path),"CWD/vertical/%s/%s",resultado,inf->nombre);

    if (rename(inf->nombre, path) !=0 ){
        perror("Error al mover el archivo");
        return 1;
    }

    printf("El archivo '%s' ha sido movido a vertical\n", inf->nombre);
    return 0;
}

int main(){
    
    InfoLinea test;

    test.cant_letras = 50;
    test.cant_lineas = 50;
    strcpy(test.nombre, "Miguel.txt");
    strcpy(test.tipo, "vertical");
    
    char cwd[256];
    
    if (getcwd(cwd, sizeof(cwd)) == NULL){
        perror("Exploto");
        return 1;
    }

    if (c_inicio() != 0){
        return 1;
    }

    if (chdir(cwd) != 0){
        perror ("Error");
        return 1;
    }

    moverArchivoVertical(&test);


    
    



    return 0;
}