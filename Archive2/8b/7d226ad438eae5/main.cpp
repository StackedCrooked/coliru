#include <stdio.h>
#include <errno.h>
#include <string.h>
 
int main(void)
{
    FILE *fp;
    char *path = "/path/to/non_existing_file";
 
    errno = 0;
    if ((fp = fopen(path, "r")) == NULL) {
        char *error_str = strerror(errno);
        printf("Can't open \"%s\": %s\n", path, error_str);
    }
    printf("Error string for EINVAL: %s\n", strerror(EINVAL));
 
    return 0;
}