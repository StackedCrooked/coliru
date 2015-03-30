struct S {
    constexpr S() {}

    constexpr S &foo() {i = 5; return *this;}

    int i = 0;
};

int main() {
    static_assert(S{}.foo().i == 5);
}