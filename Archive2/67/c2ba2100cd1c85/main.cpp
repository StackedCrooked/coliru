#include <stdio.h>

struct test {
    int x;
};

void modify(struct test t) {
    t.x = 20;
}

int main(void) {
    struct test mine = { 45 };
    printf("%d\n", mine.x);
    modify(mine);
    printf("%d\n", mine.x);
}
    