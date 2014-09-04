#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
 
int main(void)
{
    char str[] = "22.01.2002";
    int i = 0;
    int len = strlen(str);
    char *num;
    unsigned long ulDate;
    
    int a1, a2, a3 =0;
    a1 = strtol(&str[0],&num,0);
    a2 = strtol(&str[3],&num,0);
    a3 = strtol(&str[6],&num,0);
    if((0<=a1<=31)&&(1<=a2<=12)&&(1792<=a3<=2208))
    {
        ulDatum = a3;
	    ulDatum <<= 8;
	    ulDatum += a2;
	    ulDatum <<= 8;
	    ulDatum += a1;
    }
    printf("%02d<>%02d<>%d   %u\n",a1,a2,a3,ulDatum);
    
 
    while (i < len) {
        long found = strtol(&str[i], &num, 0);
 
        if (errno) {
            perror("Error");
            exit(EXIT_FAILURE);
        } else if (found || num != &str[i]) {
            printf("Found %li at position %d\n", found, i);
            i = num - str;
        } else {
            i++;
        }
    }
 
    /* Base 36 */
    printf("\n%ld\n", strtol("XyZ",NULL,36));
 
    /* Overflow (range error) */
    errno = 0;
    printf("%ld\n", strtol("9223372036854775808",NULL,10));   // LONG_MAX+1 --> LONG_MAX
    printf("%s\n",strerror(errno));                           // range error
 
    return 0;
}