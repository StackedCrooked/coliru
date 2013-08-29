#include <stdio.h>

int main(int argc, char ** argv)
{
    fprintf(stdout, "%d\n", argc);
    fprintf(stdout, "%s\n", argv[0]);
    fprintf(stdout, "Goodbye!");
}