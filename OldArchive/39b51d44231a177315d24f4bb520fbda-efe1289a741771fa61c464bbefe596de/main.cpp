#include <iostream>

class foo {
public:
    // dit is de destructor
    ~foo() {
        std::cout << "Hello, world!\n";
    }
};

int main() {
    foo f;
    std::cout << "Yada yada.\n";
}
