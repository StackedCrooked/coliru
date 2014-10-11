#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <locale.h>
 
int main(void)
{
    // prepare a file, filled with numbers, squares, and factorials
    FILE *fp = fopen("results.dat", "w");
    if (fp == NULL) {
        perror("couldn't open results.dat for writing: ");
        return EXIT_FAILURE;
    }
    int product = 1;
    for (int i=1; i<=10; ++i) {
        fprintf(fp, "i=%d, i^2=%d, factorial(%d)=%d\n", i, i*i, i, product*=i);
    }
    fclose(fp);
 
    // now parse the file with fscanf()
    fp = fopen("results.dat", "r");
    if (fp == NULL) {
        perror("couldn't open results.dat for reading: ");
        return EXIT_FAILURE;
    }
 
    int n, sq, fact;
    while (fscanf(fp, "i=%d, i^2=%d, factorial(%*d)=%d ", &n, &sq, &fact) == 3) {
        printf("factorial(%d) = %d\n", n, fact);
    }
    fclose(fp);
 
    // sample string to parse with sscanf()
    char input[] = "25 54.32E-1 Thompson 56789 0123 56ß水";
    /* parse as follows:
       an integer, a floating-point value, a word,
       two-digit integer (digits 5 and 6)
       a floating-point value (digits 7, 8, 9)
       an integer which isn't stored anywhere
       a string of integers (digits 5 and 6)
       two wide characters, using multibyte to wide conversion */
 
    int i, j;
    float x, y;
    char str1[10], str2[4];
    wchar_t warr[2];
    setlocale(LC_ALL, "en_US.utf8");
 
    int ret = sscanf(input, "%d%f%9s%2d%f%*d %3[0-9]%2lc",
                     &i, &x, str1, &j, &y, str2, warr);
 
    printf("Converted %d fields:\ni = %d\nx = %f\nstr1 = %s\n"
                      "j = %d\ny = %f\nstr2 = %s\n"
                      "warr[0] = U+%x warr[1] = U+%x\n",
                      ret, i, x, str1, j, y, str2, warr[0], warr[1]);
    return EXIT_SUCCESS;
}