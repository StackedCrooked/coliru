#include <stdio.h>

int main()
{
    FILE* input = popen("echo $username", "r");
    char name[1024];
    fscanf(input, "%s", name);
    printf("%s", name);
}
