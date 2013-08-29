namespace foo {
    template <typename T>
    struct bar {
        bar() { }
    };

    template struct bar<int>;
}