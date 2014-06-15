struct A {
    virtual ~A() = 0;
};
A::~A() {}

struct B : A {
    virtual void f() = 0;
};

struct C : B {
    virtual void f() override {}
};

int main() {
    C c;
}