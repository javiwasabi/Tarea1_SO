#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct {
    int cant_lineas;
    int cant_letras;
    char nombre[100];
    char tipo[15];
} InfoLinea;

InfoLinea contador_general(const char *nombre_archivo) {
    InfoLinea info = {0, 0, ""};
    
    if (strlen(nombre_archivo) < 100){
        strcpy(info.nombre, nombre_archivo);
    } else {
        perror("Nombre del archivo es demasiado grande");
        return info;
    }


    FILE *fPointer = fopen(nombre_archivo, "r");
    
    if (fPointer) {
        char tamano[1000];
        
        if (fgets(info.tipo, sizeof(info.tipo),fPointer) != NULL){
            info.tipo[strcspn(info.tipo, "\n")] = '\0';
        } else {
            perror("Error al leer la primera linea");
        }
        
        // Empieza a contar
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
        
        // Cuenta el resto de las lineas
        while (fgets(tamano, sizeof(tamano), fPointer) != NULL) {
            info.cant_lineas++;
        }
        
        fclose(fPointer);
    } else {
        perror("Error al leer el archivo");
    }
    //info.cant_lineas ++;
    return info;
}

int main() {
    const char *nombre_archivo = "carro.txt";
    InfoLinea result = contador_general(nombre_archivo);
    
    if (result.cant_lineas > 0) {
        printf("Tipo de Resolucion: %s\n", result.tipo);
        printf("Nombre del archivo: %s\n", result.nombre);
        printf("Numero de lineas: %d\n", result.cant_lineas);
        printf("Letras por linea: %d\n", result.cant_letras); //Duplicar numero en caso de contar espacios
    }
    
    return 0;
}
