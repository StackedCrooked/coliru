#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
    // write buffer to file
    FILE *f1;
    char buffer[] = { 'x' , 'y' , 'z' };
    f1 = fopen("file.bin", "wb");
    int ret_code = fwrite(buffer, sizeof(char), sizeof(buffer), f1);
    if (ret_code < (int)sizeof(buffer))
       if (ferror(f1))
       {
          perror("fwrite()");
          fprintf(stderr,"fwrite() failed in file %s at line # %d\n", __FILE__,__LINE__-5);
          exit(EXIT_FAILURE);
       }
    fclose(f1);
 
    // read the same data and print it to the standard output
    FILE *f2;
    char rbuf[10];
    f2 = fopen("file.bin", "rb");
    const char* res = fgets(rbuf, sizeof(rbuf), f2);
    fclose(f2);
 
    if (res) { // points to rbuf on read success, NULL on failure
        puts(res);
    }
 
    return EXIT_SUCCESS;
}