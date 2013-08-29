#include <iostream>
#include <typeinfo>
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
        : value(value) {
            std::cout << '\n' << typeid(T).name();
            std::cout << '\n' << typeid(decltype(value)).name();
            }
};

int main() {
    loud ref;
    NodeBase<loud&> node(ref);
    std::cout << '\n' << &ref;
    std::cout << '\n' << &node.value;
}