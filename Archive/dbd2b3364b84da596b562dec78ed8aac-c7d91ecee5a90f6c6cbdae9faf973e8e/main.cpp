namespace foo {
    template <typename T>
    struct bar { bar() { } };
}

void baz(int x) { }

template struct foo::bar<int>;