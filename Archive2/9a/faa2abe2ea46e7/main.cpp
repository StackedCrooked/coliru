constexpr int foo();

constexpr int x = foo();

constexpr int foo() { return 42; }

int main() {}