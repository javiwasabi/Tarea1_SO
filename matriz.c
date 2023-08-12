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

char matriz(const char nombre_archivo){

    InfoLinea inf = contador_general(nombre_archivo);

    char confirnom[100] = inf.nombre;
    char Matrix[inf.cant_letras][inf.cant_lineas];

    FILE *fPointer = fopen(nombre_archivo, "r");
    int fila = 0;

    while (!feof(fPointer)){

        for(int i = 0; i < inf.cant_lineas; i++){


           if(fscanf(fPointer, "%c", &Matrix[fila][i]) == EOF){
                break;
            }else{
                if(fPointer != " "){
                    fscanf(fPointer, "%c", &Matrix[fila][i]);
                };
            }; 
        };

        fila++;

        if (fila == inf.cant_letras){
            break;
        }
    };

    fclose(fPointer);

    for(int i = 0; i< inf.cant_letras; i++){
        for(int j= 0; j< inf.cant_lineas; j++){
            printf("%c", Matrix[i][j]);
        }
        printf('\n');

    };

}

int main(){
    matriz('perro.txt');

}