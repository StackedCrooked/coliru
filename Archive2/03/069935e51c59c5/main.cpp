#include <memory>
#include <iostream>

struct Base {};
struct Derived : public Base {};

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

int main() {
    std::unique_ptr<Base> b = make_unique<Derived>();
    std::cout << "You suck.";
}