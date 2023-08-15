#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

typedef struct {
    int cant_lineas;
    int cant_letras;
    char nombre[100];
    char tipo[15];

} InfoLinea;

InfoLinea * inicial(int * cont){
    int tamano = 12;
    int contador = 0;
    InfoLinea * lista_general = malloc (tamano * sizeof(InfoLinea)); //Arreglo dinamico

    if (lista_general == NULL){
        perror("Error al alocar memoria para la lista");
        //return;
    }

    DIR * directory;
    struct dirent * entry;

    directory = opendir(".");


    if (directory == NULL){
        printf("Error al abrir la carpeta\n");
        //return;
    }

    while ((entry = readdir(directory)) != NULL){
        
        //Segun una documentacion, si d_type es 8, significa que estas hablando de un archivo, no un directorio
        if (entry->d_type == 8 && strstr(entry->d_name,".txt") !=NULL && strcmp(entry->d_name + strlen(entry->d_name)-4,".txt") == 0 && strcmp(entry->d_name, "README.txt") != 0){
            //printf("File: %s\n", entry->d_name);
            strcpy(lista_general[contador].nombre,entry->d_name);
            contador++;
            //Ahora de paso crearemos un arreglo dinamico del tamaño exacto a los casos donde el archivo termina en txt
        }
        
    }

    if (closedir(directory) == -1){
        printf("Error al cerrar el archivo\n");
        //return;
    }

    *cont = contador;

    return lista_general;
}

void contador_general2(InfoLinea * inf){
    FILE *fPointer = fopen(inf->nombre, "r");
    
    if (fPointer) {
        char tamano[1000];
        if (fgets(inf->tipo, sizeof(inf->tipo), fPointer) != NULL){
            inf->tipo[strcspn(inf->tipo,"\n")] = '\0';
        } else {
            perror("Error al leer la primera linea");
        }

        if (fgets(tamano, sizeof(tamano), fPointer) != NULL) {
            inf->cant_lineas = 1;
            for (int i = 0; tamano[i] != '\0'; i++){
                if (isalpha(tamano[i])){
                    inf->cant_letras++;
                }
            }
        } else {
            perror("Error al leer la segunda linea, ¿Seguro que el archivo esta correcto?");
        }

        while (fgets(tamano, sizeof(tamano),fPointer)!= NULL){
            inf->cant_lineas++;
        }

        fclose(fPointer);
    } else {
        perror("Error al leer el archivo");
    }

    //printf("EUREKAAAAAA\n");
}
void matriz(InfoLinea * infosuck){

    char Matrix[infosuck->cant_letras][infosuck->cant_lineas];

    FILE * file = fopen(infosuck->nombre,"r");

    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }


    int fila = 0;

   

    while (fila < infosuck->cant_letras && !feof(file)){
        

        for(int i = 0; i < infosuck->cant_lineas; i++){
            char c = fgetc(file);


        for(int i = 0; i < infosuck->cant_lineas; i++){
            char c = fgetc(file);


           if(c == EOF || c == '\n'){
                break;
            }if (c != ' ') {
                Matrix[fila][i] = c;
            }; 
        };

        fila++;

        if (fila == infosuck->cant_letras){
            break;
        }
    };

    fclose(file);
    printf("%i" , infosuck->cant_letras);
     

    for(int i = 0; i< infosuck->cant_letras; i++){
        for(int j= 0; j< infosuck->cant_lineas; j++){
            printf("%c", Matrix[i][j]);
        }
        printf("\n");
        


    };
   

}

int main(){

    int cont;


    InfoLinea * result = inicial(&cont);

    for (int i = 0; i < cont; i++){

        
        printf("El nombre del archivo es: %s\n", result[i].nombre);
        printf("La orientacion del archivo: %s\n", result[i].tipo);
        printf("La dimension horizontal es: %d\n", result[i].cant_letras);
        printf("La dimension vertical es: %d\n", result[i].cant_lineas);
    }
 
    // matriz(&result[0]);
    return 0;

