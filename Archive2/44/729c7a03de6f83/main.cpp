#include <stdio.h>

void print_array(char **array[]) {
    for(char** p = *array; *p; p++)
        printf("%s\n", *p);
}

int main() {
    print_array((char**[]){(char*[]){"hello", "world", 0}});
}
