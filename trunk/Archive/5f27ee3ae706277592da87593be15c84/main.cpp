#include <stdio.h>

int main(int argc, char ** arv)
{
    fprintf(stdout, "%d", argc);
    fprintf(stdout, "%s", argv[0]);
}