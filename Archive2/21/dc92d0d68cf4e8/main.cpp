#include <stdio.h>

struct s {
    int x;
};

void f(struct s s) {
    ++s.x;
}

int main() {
    struct s s = { .x = 1 };
    printf("%d\n", s.x);
    f(s);
    printf("%d\n", s.x);
    return 0;
}
