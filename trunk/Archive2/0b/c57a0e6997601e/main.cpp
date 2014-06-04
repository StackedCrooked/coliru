#include <iostream>

class A {
protected:
    int a;
};

class B : public A {
public:
    using A::a;
}

int main() {
    B b;
    b.a = 5;
}
