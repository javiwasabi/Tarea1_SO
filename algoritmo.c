#include "algoritmo.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

InfoLinea contador_general(const char *nombre_archivo) {
    InfoLinea info = {0, 0, ""};
    
    if (strlen(nombre_archivo) < 100) {
        strcpy(info.nombre, nombre_archivo);
    } else {
        perror("Nombre del archivo es demasiado grande");
        return info;
    }

    FILE *fPointer = fopen(nombre_archivo, "r");
    
    if (fPointer) {
        char tamano[1000];
        
        if (fgets(info.tipo, sizeof(info.tipo), fPointer) != NULL) {
            info.tipo[strcspn(info.tipo, "\n")] = '\0';
        } else {
            perror("Error al leer la primera linea");
        }
        
        if (fgets(tamano, sizeof(tamano), fPointer) != NULL) {
            info.cant_lineas = 1;
            for (int i = 0; tamano[i] != '\0'; i++) {
                if (isalpha(tamano[i])) { // Chequea si el caracter es una letra
                    info.cant_letras++;
                }
            }
        } else {
            perror("Error al leer la segunda linea");
        }
        
        while (fgets(tamano, sizeof(tamano), fPointer) != NULL) {
            info.cant_lineas++;
        }
        
        fclose(fPointer);
    } else {
        perror("Error al leer el archivo");
    }
    
    return info;
}
