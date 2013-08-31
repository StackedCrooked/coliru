#include <string>
#include <iostream>

template<class T>
struct NodeBase
{
    T value;
    NodeBase(T &&value)
        : value(std::forward<T>(value)) { }
};

std::string foo (void)
{
    return std::string("foo");
}

int main() {
    std::string bar("bar");
    NodeBase<std::string> n(std::move(bar));
    std::cout << "n.base: " << n.value << std::endl;
    std::cout << "bar: " << bar << std::endl;
}