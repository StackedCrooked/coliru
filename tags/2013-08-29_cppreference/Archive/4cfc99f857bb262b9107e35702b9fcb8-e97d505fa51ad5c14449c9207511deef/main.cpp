#include <functional>
#include <iostream>
#include <vector>

class Barbar {
private:
    void foo() {
        ++myvar;
        std::cout << myvar << std::endl;
    }
public:
    int myvar = 1337;
    std::function<void()> call_foo{std::bind(&Barbar::foo, this)};
};

int main() {
    Barbar n;
    n.myvar = 101;
    n.call_foo();
    std::cout << n.myvar << std::endl;
}