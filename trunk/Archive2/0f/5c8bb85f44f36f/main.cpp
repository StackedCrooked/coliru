#include <string>
#include <iostream>

struct Foo {
    Foo(void *) {
        std::cout << "Foo's constructor\n";
    }
};

const Foo &bar() {
    return NULL;
}

int main() {
    bar();
}

