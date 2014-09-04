#include <iostream>
#include <utility>

class test
{
private:
    test() { }
public:
    test foo() { return *this; }

    static const char *name() { return "test"; }
};

int main()
{
    std::cout << decltype(test().foo())::name() << std::endl;               // 1
    std::cout << decltype(std::declval<test>().foo())::name() << std::endl; // 2
}