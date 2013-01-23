#include <stdio.h>

void* foo() {
    return reinterpret_cast<void*>(&foo);
}

int main() {
    perror("Error");
}
