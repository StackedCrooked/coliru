namespace foo {
    void bar() {
    }
    struct Type;
}

int main() {
    using Hi = foo::Type;
    using hello = foo::bar;
}
