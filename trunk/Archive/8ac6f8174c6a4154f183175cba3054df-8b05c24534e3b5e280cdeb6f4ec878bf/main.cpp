struct A {};
struct B {};

A foo() { return {}; }

template <typename T>
struct bar {
    bar() { T x = foo(); }
};

int main() {
    bar<B> x;
}
