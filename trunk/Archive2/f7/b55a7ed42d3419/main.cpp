namespace N {
    struct S{};
    void foo(int) { }
}

template<typename T>
int constexpr bar(T) {
    return 42;
}

int main() {
    foo(bar(N::S{}));
    return 0;
}
