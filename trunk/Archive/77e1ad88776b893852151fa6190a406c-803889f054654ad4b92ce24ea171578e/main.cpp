#include <iostream>
struct loud {
    loud() {}
    loud(const loud&) {std::cout << "C";}
    loud(loud&&) {std::cout << "M";}
};

template<class T>
struct NodeBase
{
    T value;
    NodeBase(T &&value)
        : value(value) { }
};

int main() {
    loud ref;
    NodeBase<loud&> node(ref);
    std::cout << '\n' << &ref;
    std::cout << '\n' << &node.value;
}