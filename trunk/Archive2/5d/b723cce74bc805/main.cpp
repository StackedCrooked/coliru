#include <iostream>
#include <memory>
#include <string>

class Foo {
public:
    Foo(const std::string& i_name) : name(i_name) {}

    std::function<void()> GetPrinter() {
        return [this]() {
            std::cout << name << std::endl;
        };
    }

    std::string name;
};

int main() {
    std::function<void()> f;

    {
        auto foo = std::make_shared<Foo>("OK");
        f = foo->GetPrinter();
    }

    auto foo = std::make_shared<Foo>("WRONG");

    f();

    return 0;
}