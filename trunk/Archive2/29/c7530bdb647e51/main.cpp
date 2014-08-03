struct A {
    ~A() {}

    void foo() {
        this->~A();
    }
};

int main() {
    A a;
    a.foo();
}
