struct A {
    auto f() & {}
    auto f() && {}
};

int main() {
    A{}.f();
    A a;
    a.f();
}
