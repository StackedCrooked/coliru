#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
 
int main() 
{
    /* Decimal */
    printf("%lu\n", strtoul("",NULL,10));        /* empty string           */
    printf("%lu\n", strtoul(" +0123",NULL,10));  /* leading space and zero */
    printf("%lu\n", strtoul("-123",NULL,0));
 
    /* Binary */
    printf("%lu\n", strtoul("1100", NULL,2));
 
    /* Octal */
    printf("%lu\n", strtoul("14",NULL,8));
    printf("%lu\n", strtoul("014",NULL,0));
 
    /* Base 13 */
    printf("%lu\n", strtoul("1c",NULL,13));
 
    /* Hexadecimal */
    printf("%lu\n", strtoul("FFFFFFFFFFFFFFFF",NULL,16));
    printf("%lu\n", strtoul("0xFFFFFFFFFFFFFFFF",NULL,0));
 
    /* Base 36 */
    printf("%lu\n", strtoul("XyZ",NULL,36));   /* 44027 */
 
    /* Overflow, a value too large for type unsigned long int. */
    errno = 0;
    printf("%lu\n", strtoul("18446744073709551616",NULL,10));
    printf("errno = %d\n", errno);   /* 34, range error */
 
    /* Underflow. a value too small for type unsigned long int. */
    errno = 0;
    printf("%lu\n", strtoul("-1",NULL,10));
    printf("errno = %d\n", errno);   /*  0 */
 
    /* Using str_end. */
    char *str_end;
    printf("%lu\n", strtoul("  00123 999",&str_end,10));
    printf("[%c]\n", *str_end);
    printf("%lu\n", strtoul(str_end,NULL,10)); 
 
    return 0;
}