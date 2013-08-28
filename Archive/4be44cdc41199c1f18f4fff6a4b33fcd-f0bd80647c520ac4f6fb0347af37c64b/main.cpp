namespace my {
    class foo {
        friend void f(foo const&) {}
    };
}

int main() {
    f(my::foo());
    my::f(my::foo());
}