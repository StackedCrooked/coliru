#include <cstdio>
using namespace std;

// If x is large enough, rougly this code is generated

struct x { int dummy[1024]; };

void make_x(x* x1) {
  
    printf("original x address %p\n", x1);
}

int main() {
    x x1;
    make_x(&x1);
    printf("copy  of x address %p\n", &x1);
}
