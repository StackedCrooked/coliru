struct A {};
struct B {};

A foo() { return {}; }

template <typename T>
struct bar {
    bar() { auto x = foo(); }
};

int main() {
    bar<A> x;
}
