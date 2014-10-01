#include <iostream>
     
struct foo {
    foo( foo const& ) { std::cout << "copy\n"; };
    foo( foo && ) { std::cout << "move\n"; };
    foo() = default;
};
     
struct bar {
    foo f;
    bar& operator=( bar ) = default;
};
     
int main() {
    bar b;
    b = {};
}