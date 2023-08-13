#ifndef ALGORITMO_H
#define ALGORITMO_H

typedef struct {
    int cant_lineas;
    int cant_letras;
    char nombre[100];
    char tipo[15];
} InfoLinea;

void contador_general2(InfoLinea * inf);

void horizontal(InfoLinea * infosuck);
int horizontal_aux(char * nombre, char * str);

InfoLinea * inicial();


#endif
