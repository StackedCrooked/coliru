#include <stdio.h>
#if 1
int main(int ac, char **av) {
    printf("hello, world %s\n", av[1]);
}
#else
int main() {
    puts("Hallo xWalter");
}
#endif