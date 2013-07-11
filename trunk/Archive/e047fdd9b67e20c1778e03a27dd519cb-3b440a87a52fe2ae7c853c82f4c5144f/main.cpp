int main() {
    struct Foo {void bar();};
    auto ptr = &Foo::bar;
}
