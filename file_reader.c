#include <stdio.h>
#include <ctype.h>

typedef struct {
    int cant_lineas;
    int cant_letras;
} InfoLinea;

InfoLinea contador_general(const char *nombre_archivo) {
    InfoLinea info = {0, 0};
    
    FILE *fPointer = fopen(nombre_archivo, "r");
    
    if (fPointer) {
        char tamano[1000];
        
        // Se salta la primera linea
        if (fgets(tamano, sizeof(tamano), fPointer) == NULL) {
            perror("Error al leer la primera linea");
            fclose(fPointer);
            return info;
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
    info.cant_lineas ++;
    return info;
}

int main() {
    const char *nombre_archivo = "banco.txt";
    InfoLinea result = contador_general(nombre_archivo);
    
    if (result.cant_lineas > 0) {
        printf("Numero de lineas: %d\n", result.cant_lineas);
        printf("Letras por linea: %d\n", result.cant_letras);
    }

    return 0;
}
