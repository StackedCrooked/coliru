struct B {
protected:
    int foo;
};

struct D : B {
    void bar() {
        B b;
        b.foo = 0;
    }
};

int main() {
    D d;
    d.bar();
}