#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int createFolder(const char *foldername) {
    if (mkdir(foldername,0777) != 0) {
        perror("Error creating folder");
        return 1;
    }

    printf("Folder '%s' created successfully!\n", foldername);

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

int main() {
    // Creating a folder
    if (createFolder("myfolder") != 0) {
        return 1;
    }

    // Moving a file to the folder
    if (moveFileToFolder("myFile.txt", "myfolder") != 0) {
        return 1;
    }

    return 0;
}
