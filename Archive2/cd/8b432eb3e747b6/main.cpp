struct A {
    ~A() {}

    void foo() {
        A::~A(0);
    }
};

int main() {
    A a;
    a.foo();
}
