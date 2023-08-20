#include "algoritmo.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>


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
            perror("Error al leer la primera linea en:");
            printf("%s\n", inf->nombre);
        }

        if (fgets(tamano, sizeof(tamano), fPointer) != NULL) {
            inf->cant_lineas = 1;
            for (int i = 0; tamano[i] != '\0'; i++){
                if (isalpha(tamano[i])){
                    inf->cant_letras++;
                }
            }
        } else {
            //perror("Error al leer la segunda linea, ¿Seguro que el archivo esta correcto?");
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

void horizontal_2(InfoLinea * inf){
    clock_t start, end;
    double cpu_time;
    start = clock();

    char auxNom[20];
    strcpy(auxNom, inf->nombre);

    size_t tamano = strlen(auxNom);
    
    if (tamano > 4 && strcmp(auxNom + tamano - 4, ".txt") == 0){
        auxNom[tamano -4] = '\0';
    }

    for (size_t i = 0; i < tamano; i++) {
        auxNom[i] = toupper(auxNom[i]);
    }

    
    //printf("El nombre del archivo es: %s , y luego queda en %s\n", inf->nombre, auxNom);

    bool flag = false;

    FILE * file = fopen(inf->nombre, "r");
    if (file){
        char linea[1000];
        while (fgets(linea, sizeof(linea), file) != NULL){
            char nlinea[1000];
            int minicont = 0;

            for (int i = 0; linea[i] != '\0'; i++){
                if (!isspace(linea[i])){
                    nlinea[minicont] = linea[i];
                    minicont++;
                }
            }

            nlinea[minicont] = '\0';
            
            char * resultado = strstr(nlinea,auxNom);

            if (resultado != NULL){
                printf("Se ha hecho un match\n");
                end = clock();
                cpu_time = ((double)(end-start))/CLOCKS_PER_SEC;
                printf("Tiempo de demora: %f segundos\n", cpu_time);
                flag = true;
            }
        }

        if (flag == false){
            printf("No se ha hecho un match\n");
            end = clock();
        }
        fclose(file);
        //printf("Archivo cerrado correctamente\n");
    }

}

void horizontal(InfoLinea * infosuck) {
    clock_t start, end;
    double cpu_time;
    start = clock();

    bool flag = false;
    FILE * file = fopen(infosuck->nombre,"r");
    if (file){
        char linea[1000];
        while (fgets(linea, sizeof(linea),file) != NULL){
            char nlinea[1000];
            int minicont = 0;

            for (int i = 0; linea[i] != '\0'; i++){
                if (!isspace(linea[i])){
                    nlinea[minicont] = linea[i];
                    minicont++;
                }
            }

            nlinea[minicont] = '\0';
            if (horizontal_aux(infosuck->nombre,nlinea) == 1){
            
                printf("Felicitaciones, se ha encontrado la palabra\n");
                end = clock();
                cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
                printf("Tiempo de demora: %f segundos\n",cpu_time);
                flag = true;
                break;
            }
        }

        fclose(file);

    }
    if (flag == false){
        printf("No se ha encontrado la palabra\n");
        end = clock();
    }
}

int horizontal_aux(char * nombre, char * str){
    char auxNom[20];
    strcpy(auxNom,nombre);
    size_t len = strlen(auxNom);
    if (len >= 4){
        auxNom[len - 4] = '\0';
    } else {
        perror("El nombre del archivo es demasiado corto");
    }

    for (int i = 0; auxNom[i] != '\0'; i++){
        auxNom[i] = toupper(auxNom[i]);
    }

    char * resultado = strstr(str,auxNom);

    if (resultado != NULL){
        //printf("Se hace hecho un match\n");
        return 1;
    } else {
        //printf("No se ha encontrado la palabra\n");
        return 0;
    }
}

/*FUNCIONES PARA LA CREACION DE CARPETAS*/

void subPalabra(int num1, int num2, char * resultado){
    char resultado1[100];
    char resultado2[100];

    snprintf(resultado1, sizeof(resultado1), "%d", num1);
    snprintf(resultado2, sizeof(resultado2), "%d", num2);

    snprintf(resultado, strlen(resultado1) + strlen(resultado2) + 4, "%sx%s", resultado1, resultado2);

}

int createFolder(const char *foldername) {
    int resultado = mkdir(foldername, 0777);
    if (resultado == 0){
        //printf("Folder '%s' created successfully!\n", foldername);
        return 0;
    } else {
        if (errno == EEXIST) {
            //fprintf(stderr, "La carpeta '%s' ya existe\n", foldername);
            return 1;
        } else {
            perror("Error en la creacion de archivos\n");
            return -1;
        }
    }
}

int moverArchivo(InfoLinea * inf){
    char path[256];
    char aux_nom [100];
    char direc[10];

    subPalabra(inf->cant_letras, inf->cant_lineas, direc);

    strcpy(aux_nom, inf->nombre);

    //printf("El lugar a mover es: CWD/%s/%s\n", "horizontal", aux_nom);
    if (strcmp(inf->tipo, "horizontal") == 0){
        snprintf(path, sizeof(path), "CWD/horizontal/%s/%s", direc,aux_nom);
        //printf("Ahora moveremos el archivo: %s a su destino horizontal\n", aux_nom);
    } else {
        snprintf(path, sizeof(path), "CWD/vertical/%s/%s", direc,aux_nom);
        //printf("Ahora moveremos el archivo: %s a su destino vertical\n", aux_nom);
    }
    
    if (rename(aux_nom, path) != 0){
        perror("Error al mover el archivo");
        return 1;
    }
    return 0;
}

int crearCarpetaDimension(char * buffer, size_t size, InfoLinea * inf) {
    
    char resultado[15];
    subPalabra(inf->cant_letras,inf->cant_lineas,resultado);
    
    if(getcwd(buffer, size) == NULL){
        perror("getcwd fallo");
        return 1;
    }

    if (chdir("CWD") != 0){
        return 1;
    }

    if (strcmp(inf->tipo, "horizontal") == 0){
        
        if (chdir("horizontal") != 0){
            return 1;
        }

        //ESta lina es especifico para el nombre "50x50";
        if (createFolder(resultado) != 0){

        }

        if (chdir(buffer) != 0){
            return 1;
        }
    } else {

        if (chdir("vertical") != 0){
            return 1;
        }

        //ESta lina es especifico para el nombre "50x50";
        if (createFolder(resultado) != 0){

        }

        if (chdir(buffer) != 0){
            return 1;
        }
        
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


void vertical(InfoLinea * infosuck){
    clock_t start, end;
    double cpu_time;
    start = clock();
// Creacion de matriz
    char Matrix[infosuck->cant_letras][infosuck->cant_lineas];
    FILE * file = fopen(infosuck->nombre,"r");

    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    int fila = 0;

    while (fila < infosuck->cant_lineas && !feof(file)){     
        int p;

        while ((p = fgetc(file)) != EOF && p!= '\n') {   //salto de la primera linea 
        }

        for(int i = 0; i < infosuck->cant_letras; i++){

            char c = fgetc(file);
            if(c == EOF ){
                break;
            }else if (c != ' ') {
                Matrix[fila][i] = c;
                
            }else if (c != '\n') {
                Matrix[fila][i] = c;
             
                
            }if (c == ' '){
                i--;
            }; 
        };

        fila++;

        if (fila == infosuck->cant_letras){
            break;
        }
    };

    fclose(file);
    
/* Ver matriz

for(int i = 0; i< infosuck->cant_letras; i++){
        for(int j= 0; j< infosuck->cant_lineas; j++){
            printf("%c", Matrix[i][j]);
        }
        printf("\n");    
    };
*/   

// Busqueda dentro de la matriz
    bool flag = true;
    char *p = &infosuck->nombre[0];
   
    for (int c = 0; c < infosuck->cant_letras; c++) { 
        int num= 0;
       
        for (int f = 0; f< infosuck->cant_lineas; f++) { 
                   
            if (toupper(p[num]) == Matrix[f][c]) { 
            
                if (p[num+1] == '.') { 

                    printf("\nSe ha encontrado la palabra con éxito\n");
                
                    end = clock();
                    cpu_time = ((double)(end-start))/CLOCKS_PER_SEC;
                    printf("Tiempo de demora: %f segundos\n", cpu_time);
                    printf("La palabra es: \n");

                    while (num >=0){
                        printf(" %c", Matrix[f-num][c]);
                        num--;
                    };
                    printf("\n");
                   
                    flag = false;
                    break; 
                }
                num++;
            }
            else {
            num = 0; 
            }       
        }

        if (!flag) {
            break; // Terminar el bucle externo si se encuentra la palabra
        }
    }

    if (flag) {
    
    }
    end = clock();

};

bool comparar(char linea[], char palabra[], int cantidad, int largo) {
    int i = 0;
    bool flag = false;
  
    while (i != largo-1 && !flag) {
        int num = 0;
       

        if (linea[i] == toupper(palabra[0])) {

            while (palabra[num] != '.') {

                if (linea[i] != toupper(palabra[num])) {
                    flag = false;
                    break;
                } else if (num == cantidad -1 && linea[i] == toupper(palabra[num])) {
                    flag = true;
                    printf("Encontraste la palabra!!\n");
                    break;
                }
                num++;
                i++;
            }
        } else {
            i++;
        }
    }
    return flag;
}
void vertical2(InfoLinea * infosuck){

// Creacion de matriz
    char Matrix[infosuck->cant_letras][infosuck->cant_lineas];
    FILE * file = fopen(infosuck->nombre,"r");
    
    if (file == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    int fila = 0;

    while (fila < infosuck->cant_lineas && !feof(file)){     
        int p;

        while ((p = fgetc(file)) != EOF && p!= '\n') {   //salto de la primera linea 
        }

        for(int i = 0; i < infosuck->cant_letras; i++){

            char c = fgetc(file);
            if(c == EOF ){
                break;
            }else if (c != ' ') {
                Matrix[i][fila] = c;
                
            }else if (c != '\n') {
                Matrix[i][fila] = c;
                          
            }if (c == ' '){
                i--;
            }; 
        };

        fila++;

        if (fila == infosuck->cant_letras){
            break;
        }
    };

    fclose(file);
    
    int canti = 0;
    canti += infosuck->cant_letras;

    char word[20];
    strcpy(word, infosuck->nombre);
    size_t tamano = strlen(word);
    if (tamano > 4 && strcmp(word+ tamano - 4, ".txt") == 0){
        word[tamano -4] = '\0';
    }

    int letterCount = 0;

    for (int i = 0; word[i] != '\0'; i++) {
        if (isalpha(word[i])) {
            letterCount++;
        }
    }
    
    

    for (int c = 0; c < infosuck->cant_letras; c++) { 
        char palabran[infosuck->cant_letras];
        int num= 0;
       
        for (int f = 0; f< infosuck->cant_lineas; f++) { 

            palabran[num] = Matrix[c][f];
            num++;
                
        }  
        int num_chars = sizeof(palabran) / sizeof(palabran[0]);
        int num_c = sizeof(word) / sizeof(word[0]);

        bool banderita = comparar(palabran,word, letterCount, num_chars);

        if (banderita){
            break;
        }
 
    }

    
};


