#include <stdio.h>


#ifndef ALGORITMO_H
#define ALGORITMO_H

typedef struct {
    int cant_lineas;
    int cant_letras;
    char nombre[100];
    char tipo[15];
} InfoLinea;


/*FUNCIONES PARA EL USO DEL ARREGLO DINAMICO */
void contador_general2(InfoLinea * inf);

InfoLinea * inicial(int * cont);


/* FUNCIONES PARA EL USO DE LOS ALGORITMOS*/
void horizontal(InfoLinea * infosuck);

int horizontal_aux(char * nombre, char * str);

/* FUNCINOES PARA LA CREACION DE LAS CARPETAS*/

int _inicio(char * buffer, size_t size);

void subPalabra(int num1, int num2, char * resultado);

int createFolder(const char *foldername);

int moverArchivo(InfoLinea * inf);

int crearCarpetaDimension(char * buffer, size_t size, InfoLinea * inf);


#endif
