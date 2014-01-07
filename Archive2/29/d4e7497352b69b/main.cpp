#include <memory>
#include <iostream>

class Base {
public:
    virtual void callMe() { std::cout << "called base"; };
};

class Derived : public Base {
public:
    virtual void callMe() {  std::cout << "called derived"; };
};

int main() {
    std::unique_ptr<Base> pointer(new Derived());
    pointer->callMe();
    return 0;
}