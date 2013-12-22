#include <iostream>

class A {
public:
    virtual void f() = 0;
};

class B {
public:
    virtual void f() = 0;
};

template <typename C>
class AC : public A {
public:
    void f() override {
        static_cast<C&>(*this).f_from_A();
    }
};

template <typename C>
class BC : public B {
public:
    void f() override {
        static_cast<C&>(*this).f_from_B();
    }
};

class C : public AC<C>, public BC<C> {
public:
    void f_from_A() {
        std::cout << "f_from_A called.\n";
    };
    void f_from_B() {
        std::cout << "f_from_B called.\n";
    };
};

int main() {
    C c;
    A& a = c;
    B& b = c;
    a.f();
    b.f();
}
