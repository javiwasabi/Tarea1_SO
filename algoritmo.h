#ifndef ALGORITMO_H
#define ALGORITMO_H

typedef struct {
    int cant_lineas;
    int cant_letras;
    char nombre[100];
    char tipo[15];
} InfoLinea;

InfoLinea contador_general(const char *nombre_archivo);

void contador_general2(InfoLinea * inf);

void horizontal(InfoLinea * infosuck);
int horizontal_aux(char * nombre, char * str);

InfoLinea * inicial();

char matriz(char * nombre_archivo);
void vertical(char nom[], const char nomb);

#endif
