#include <iostream>
#include <memory>

struct with_copy {
    with_copy() = default;
    with_copy(with_copy const&) { std::cout << "copy ctor" << std::endl; }
};

struct foo {
    with_copy c;
    std::unique_ptr<int> p;
};

int main() {
    with_copy w = with_copy();
    
    foo a;
    //foo b = std::move(a);
}