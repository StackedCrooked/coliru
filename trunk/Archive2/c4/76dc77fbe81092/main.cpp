struct Bar {
    template<typename>
    void baz() {
    }
};

template<typename>
struct Foo {
    Bar bar;

    Foo() {
        this->bar.template baz<int>();
    }
};

int main() {
    return 0;
}