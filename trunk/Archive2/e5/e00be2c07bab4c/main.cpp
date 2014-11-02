#include <iostream>

class foo {
    public:
        void aMethod() const {
            std::cout << "Sup\n";
        }

    foo() { }
    ~foo() { }
};

int main() {
    foo f;
    f.aMethod();
}