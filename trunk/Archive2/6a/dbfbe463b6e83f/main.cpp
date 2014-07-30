#include <iostream>
#include <exception>
#include <stdexcept>
 
struct Foo {
    ~Foo() {
        if (std::uncaught_exception()) {
            std::cout << "~Foo() called during stack unwinding\n";
        } else {
            std::cout << "~Foo() called normally\n";
        }
    }
};
int main()
{
    Foo f;
    try {
        Foo f;
        std::cout << "Exception thrown\n";
        throw std::runtime_error("test exception");
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }
}