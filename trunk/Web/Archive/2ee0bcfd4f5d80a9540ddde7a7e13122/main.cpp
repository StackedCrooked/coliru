#include <stdio.h>

int main(int argc, char ** argv)
{
    fprintf(stdout, "%d", argc);
    fprintf(stdout, "%s", argv[0]);
}