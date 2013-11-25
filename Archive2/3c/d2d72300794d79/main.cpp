#include <iostream>

class B {
public:
    virtual ~B() = default;

    virtual void foo() { }
};

class D : public B {
    int x;

    virtual void foo() override {
        std::cout << x << '\n';
    }
};

void bar(B& x) {
    x.foo();
}

int main() {
    B x = D();
    bar(x);
    return 0;
}
