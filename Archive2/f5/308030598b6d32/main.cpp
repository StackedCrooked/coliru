#include <stdio.h>

void print_array(const char *const array[]) {
    while(*array) {
        printf("%s\n", *array++);
    }
}

int main() {
    print_array((const char*[3]){"hello", "world", 0});
}
