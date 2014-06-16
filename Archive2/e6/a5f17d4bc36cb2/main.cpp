#include <iostream>
#include <string>
#include <type_traits>

class Base
{
public:
    virtual std::string Foo()
    {
        return "Base";
    }
};

template <typename T>
class Derived : public Base
{
public:
    virtual std::string Foo() override
    {
        return do_Foo(std::is_same<T, float>{});
    }
    
private:
    std::string do_Foo(std::true_type)
    {
        return "Derived";
    }
    std::string do_Foo(std::false_type)
    {
        return Base::Foo();
    }
};

int main()
{
    Derived<int> testInt;
    std::cout << testInt.Foo() << std::endl;

    Derived<float> testFloat;
    std::cout << testFloat.Foo() << std::endl;//I would like this to print 'Base'
}