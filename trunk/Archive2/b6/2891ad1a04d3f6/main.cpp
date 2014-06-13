struct Foo {
    int i;
    Foo() = delete;
};
 
int main() {
    Foo f{1};
}