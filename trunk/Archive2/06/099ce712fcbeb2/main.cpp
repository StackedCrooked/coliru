#include <stdio.h>
#include <stdlib.h>

int main() {
    return 0;
}

FILE *openFile(char *filePath, char mode) {
    FILE *fp = NULL;
    char strmode[2];
    strmode[0] = mode;
    fp = fopen(filePath, &strmode);

    if (fp == NULL) {
        perror("Could not open file");
        exit(0);
    }

    return fp;
}
