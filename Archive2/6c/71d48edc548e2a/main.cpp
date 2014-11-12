#include <stdio.h>
#include <stdlib.h>
int main()
{

    FILE *fp;
    char *line = (char*)malloc(1024 * sizeof(char));
    int index = 0;
    char c;

    fp = popen("cat /dev/urandom | od", "r");
    while (true)
    {
        c = fgetc(fp);
        if (c == '\n') {
            break;
        }
        line[index++] = c;
    }
    line[index] = '\0';
    printf ("%s\n", line);
    printf("Finished\n");
}
