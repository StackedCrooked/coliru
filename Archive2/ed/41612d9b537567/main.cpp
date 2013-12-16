template <typename Derived>
struct BaseImpl
{
    // normal stuff
    int foo() const { return 42; }

    // CRTP stuff
    Derived make_new() const 
    {
        return Derived("test 123");
    }
};

#include <string>

struct MyStruct : BaseImpl<MyStruct>
{
    std::string value;
    MyStruct(std::string const& value) : value(value) {}
};

#include <iostream>

int main()
{
    MyStruct a("first");
    MyStruct b = a.make_new();

    std::cout << a.value << "\n"
              << b.value << "\n";
}
