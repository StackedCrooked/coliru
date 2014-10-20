#include <iostream>
#include <algorithm>

struct A {
    int a;
};

void foo(A *in) {
    delete in;
}

int main() {

    A a;
    
    foo(&a);

  
    return 0;
}