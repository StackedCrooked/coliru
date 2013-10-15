#include <cstdio>
using namespace std;

// If x is small / empty, rougly this code is generated

struct x { };

void make_x() {
    x tmp;
    printf("original x address %p\n", &tmp);
}

int main() {
    x x1;
    make_x();
    printf("copy  of x address %p\n", &x1);
}
