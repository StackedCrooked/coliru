#include <stdio.h>

char ** argv_p;

int main (int argc, char* argv[]) {
    (void)argc;
    argv_p = argv;
}