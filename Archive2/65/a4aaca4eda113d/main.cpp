#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
 
int main(void)
{
    char str[] = "Is 0xff bigger than 0 or 0x00? The answer is 42.";
    int i = 0;
    int len = strlen(str);
    char *num;
 
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