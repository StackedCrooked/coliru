#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
    /* Prepare an array of f-p values. */
    #define SIZE 5
    double A[SIZE] = {1.,2.,3.,4.,5.};
    /* Write array to a file. */
    FILE * fp = fopen("test.bin", "wb");
    fwrite(A,sizeof(double),SIZE,fp);
    fclose (fp);
 
    /* Read the f-p values into array B. */
    double B[SIZE];
    fp = fopen("test.bin","rb");
    int ret_code = fread(B,sizeof(double),SIZE,fp);
    if (ret_code < SIZE)
    {
       if (feof(fp))
          printf("EOF reached\n");
       else if (ferror(fp))
            {
              perror("fread()");
              fprintf(stderr,"fread() failed in file %s at line # %d\n", __FILE__,__LINE__-8);
              exit(EXIT_FAILURE);
            }
    }
    printf("%.1f\n", B[4]);   /* print one f-p value */
 
    return EXIT_SUCCESS; 
}