#include <iostream>

class Foo {
    public:
        void Bar() & {
            std::cout
                << "This is an lvalue."
            << std::endl;
        }
        void Bar() && {
            std::cout
                << "This is an rvalue."
            << std::endl;
        }
};

int main () {
    Foo Baz;
    Baz.Bar();
    Foo().Bar();
}