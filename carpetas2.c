#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

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

int createFolder(const char *foldername) {
    if (mkdir(foldername,0777) != 0) {
        perror("Error creating folder");
        return 1;
    }

    printf("Folder '%s' created successfully!\n", foldername);

    return 0;
}

int mover_hori(char * nombre){
    char path[256];
    printf("El lugar a mover es: CWD/%s/%s\n", "horizontal", nombre);
    
    snprintf(path, sizeof(path), "CWD/horizontal/%s", nombre);

    if (rename(nombre, path) != 0){
        perror("Error al mover el archivo");
        return 1;
    }
    return 0;
}

int moveFileToFolder(const char *filename, const char *destinationFolder) {
    char newFilePath[256]; // Adjust the size as needed
    
    snprintf(newFilePath, sizeof(newFilePath), "%s/%s", destinationFolder, filename);

    if (rename(filename, newFilePath) != 0) {
        perror("Error moving file");
        return 1;
    }

    printf("File '%s' moved successfully to '%s'\n", filename, destinationFolder);

    return 0;
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
int main() {
    // Creating a folder
    // if (createFolder("myfolder") != 0) {
    //     return 1;
    // }

    // // Moving a file to the folder
    // if (moveFileToFolder("myFile.txt", "myfolder") != 0) {
    //     return 1;
    // }

    char cwd[1024];

    if (_inicio(cwd, sizeof(cwd)) != 0){
        perror("Error en la funcion '_inicio'");
    }
    

    if (mover_hori("myFile.txt") != 0){
        return 1;
    }
    

    return 0;
}
