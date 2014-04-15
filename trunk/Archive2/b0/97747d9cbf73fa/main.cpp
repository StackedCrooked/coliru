#include "stdio.h"
//#include "stdlib.h"

#define CHARS_NUM 5

int main()
{
    FILE *f;
    
    char data[CHARS_NUM];
    
    if (NULL == (f = fopen("./file", "r"))) {
        perror("Can\'t open input file");
        return 1;
    }
    
    if (0 != fseek(f, 0L, SEEK_END)) {
        perror("Can\'t seek through file");
        return 1;
    }
    
    long size = ftell(f);
    if (-1 == size) {
        perror("Can\'t seek through input file");
        return 1;
    }
    
    if (0 != fseek(f, 0L, SEEK_SET)) {
        perror("Can\'t reset the input file");
        return 1;
    }
    
    printf("Size of the file is %ld\n", size); 
    if (0 == fgets(data, CHARS_NUM, f)) {
        perror("Can\'t read the file");
        return 1;
    }
    data[CHARS_NUM-1] = '\0';
    printf("Data %s\n\n", data);
    
    
    return 0;
}
