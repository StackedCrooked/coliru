#include <iostream>


class A {
    public: 
    A() {
        std::cout << "Hello A" << std::endl;
    }
};

class B {
    public:
    B() { 
        std::cout << "Hello B" << std::endl;
    }
};

class C : public B {
    public:
    C() {
        std::cout << "Hello C" << std::endl;
    }
    private:
    static A MyA;
};

A C::MyA;

int main() {
    C ThisC;
    return 0;
}