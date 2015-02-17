#include <functional>
#include <iostream>

struct Foo {
    void foo() {
        std::cout << "Called foo";
    }
};

int main() {
    std::function<void(Foo &)> callback(&Foo::foo);
    callback();
}