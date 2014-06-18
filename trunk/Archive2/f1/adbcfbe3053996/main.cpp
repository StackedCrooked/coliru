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
 
    /* Set the file position indicator in front of third f-p value. */
    if (fseek(fp,sizeof(double)*2L,SEEK_SET) != 0)
    {
       if (ferror(fp))
       {
          perror("fseek()");
          fprintf(stderr,"fseek() failed in file %s at line # %d\n", __FILE__,__LINE__-5);
          exit(EXIT_FAILURE);
       }
    }
 
    int ret_code = fread(B,sizeof(double),1,fp);   /* read one f-p value  */
    if( ret_code == 0 ) {
        perror( "fread()");
    }
    printf("%.1f\n", B[0]);                        /* print one f-p value */
 
    fclose(fp);
    return EXIT_SUCCESS;
}