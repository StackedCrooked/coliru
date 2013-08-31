struct Foo{};

void foo(class Foo *){}

int main() {
    Foo f;
    foo(&f);
}