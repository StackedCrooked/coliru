#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
    char * buf = NULL;
    size_t buflen = 0;

    ssize_t line_len;

    while ((line_len = getline(&buf, &buflen, stdin)) > 0) {
        buf[line_len - 1] = '\0';

        char * val = getenv(buf);

        if (val) {
            printf("setenv %s \"%s\"\n", buf, val);
        }
        else {
            fprintf(stderr, "warning: %s not found\n", buf);
        }
    }

    return EXIT_SUCCESS;
}
