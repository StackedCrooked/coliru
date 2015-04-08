
#include <stdio.h>

typedef int (*fptr)(int);

fptr make_adder(int x) {
    int lambda(int y) {
        return x + y;
    }
    return lambda;
}

int main() {
    fptr add5 = make_adder(5);
    printf("%d\n", add5(2));
    return 0;
}
