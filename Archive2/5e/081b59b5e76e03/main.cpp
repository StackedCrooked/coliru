#include <cstdio>

void foo(int &c) {
    std::puts("Hello, World!\n");   
}

int main() {
    int a;

    int &b = a; // the reference is 'bound' to the object 'a'

    void foo(int &c);
    
    foo(a); // the reference parameter is bound to the object 'a' for this particular execution of foo.
}
