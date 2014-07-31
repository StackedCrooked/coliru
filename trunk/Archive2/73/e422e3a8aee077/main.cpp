#include <stdio.h>
#include <string.h>
int main(int argc, const char * argv[])
{

   char str[100] = "wksafkdhiwu fksh";
    char *p;
    p = strpbrk(str, "s");
    printf("%s", p);
    return 0;
}