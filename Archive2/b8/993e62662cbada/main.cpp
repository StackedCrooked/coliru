#include <memory>

class Base { };
class Derived : public Base { };

void f(std::unique_ptr<Base> const&);

int main() {
    std::unique_ptr<Derived> x;
    f(x);
}