#include <iostream>

class B {
public:
    void bar() {
        this->foo();
    }

private:
    virtual void foo() {
        std::cout << "B::foo()\n";
    }
};

class D : public B {
public:
    virtual void foo() override {
        std::cout << "D::foo()\n";
    }
};

int main() {
    D x;
    B& y = x;
    y.bar();
}
