struct A {
    ~A() {}

    void foo() {
        A::~A();
    }
};

int main() {
    A a;
    a.foo();
}
