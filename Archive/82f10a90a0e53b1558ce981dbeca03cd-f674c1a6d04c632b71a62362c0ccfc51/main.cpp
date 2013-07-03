#include <iostream>

struct C {
    C() {throw 0;}
};

struct A : C {
    A() {
        try {
            std::cout << "normal" << std::endl;
        } catch(...) {
            std::cout << "exception" << std::endl;
            throw;
        }
    }
};

int main()
{
    try {
        A a;
    } catch(...) {
        ;
    }
    return 0;
}
