#include <stdio.h>
#include <string.h>

int main() {
    const char a[] = {'t', 'e', 's', 't', 'i', 'n', 'g', '\0'};
    const char b[] = {'t', 'e', 's', 't'};
    const char c[] = {'i', 'n', 'g', '\0'};

    if (strncmp(a, b, sizeof(a)) == 0) {
        printf("Equal\n");
    } else {
        printf("Not Equal\n");
    }
}