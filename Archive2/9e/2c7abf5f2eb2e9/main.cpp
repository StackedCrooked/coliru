namespace N {
    struct S{};
    void bar(S const&) { }
}

template<typename T>
void foo(T const& x) {
    bar(x);
}

int main() {
    foo(N::S{});
    return 0;
}
