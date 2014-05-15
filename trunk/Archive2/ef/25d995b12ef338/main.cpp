struct A {
    int a = 0;
    constexpr A() { a = 1; }
};

constexpr bool f() {
    constexpr A a;
    static_assert(a.a == 1, ""); // L1: OK
    return a.a == 1;
}
static_assert(f(), ""); // L2: Error, can not modify A::a in constexpr

int main() {}
