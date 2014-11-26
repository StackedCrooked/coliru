#include <iostream>
#include <utility>

class Foo {
    public:
        Foo() {}

        Foo(Foo&& other) {
            value = std::move(other.value);
            other.value = 1; //since it's int!
        }

        int value;

    private:
        Foo(const Foo& other);
};


void Bar(Foo&& x) {
    std::cout << "# " << x.value << std::endl;
    Foo y=std::move(x);   //comment out
}

int main() {
    Foo foo;
    foo.value = 5;

    Bar(std::move(foo));
    std::cout << foo.value << std::endl;

    return 0;
}
