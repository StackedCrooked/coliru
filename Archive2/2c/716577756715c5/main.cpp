#include <iostream>
#include <functional>
#include <string>

class Foo {
public:
    Foo(int& y) : x(y) {}
    void foo() const
    {
        str[5] = 'x';
        x = 4;
    }
private:
    std::string str;
    std::reference_wrapper<int> x;
};

int main() {
    int y = 123;
    Foo x(y);
    x.foo();
}