struct A {
    A() = default;
    A(const A&) = delete;
    A(A&&) noexcept = default;
};

A foo() {
    A a;
    return a;
}

int main() {
    A a = foo();
    (void)a;
}
