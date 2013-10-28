#include <iostream>

class A {
    public:
        virtual void foo() const { std::cout << "A\n"; }
};
class B : public A{
    public:
        void foo() const { std::cout << "B\n"; }
};
class C: public B {
    public:
        void foo() const { std::cout << "C\n"; }
};

int main() {
    A const& a = C{};
    a.foo();
}