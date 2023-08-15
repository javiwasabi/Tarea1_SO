#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void moveFileToPath(const char *sourceFilePath, const char *destinationPath) {
    // Construct the destination file path
    char destinationFilePath[1024];  // Adjust the buffer size as needed
    snprintf(destinationFilePath, sizeof(destinationFilePath), "%s/%s", destinationPath, "myFile.txt");

    // Move the file
    int result = rename(sourceFilePath, destinationFilePath);
    if (result == 0) {
        printf("File moved successfully.\n");
    } else {
        perror("Error moving file");
    }
}

int main() {
    const char *sourceFilePath = "myFile.txt";
    const char *destinationPath = "CWD/horizontal/50x50";  // Update the destination path

    moveFileToPath(sourceFilePath, destinationPath);

    return 0;
}
