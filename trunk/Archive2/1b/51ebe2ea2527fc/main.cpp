#include <iostream>
#include <typeinfo>

template <typename TVal>
void Call(TVal &&) {
    std::cout << typeid(TVal).name() << std::endl;
}

int main() {
    Call(42);
    Call(std::string("hello"));
}
