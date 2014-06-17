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
	std::string Foo() override
	{
		return do_Foo(true);
	}
private:
    template<typename U = T>
    auto do_Foo(bool)
        -> decltype(std::declval<U>().test(), void(), std::string())
    {
        return "Derived";
    }
    std::string do_Foo(int)
    {
        return Base::Foo();
    }
};

struct Test
{
    void test() {}
};

int main()
{
	Derived<int> testInt;
	std::cout << testInt.Foo() << std::endl;

    Derived<Test> testTest;
    std::cout << testTest.Foo() << std::endl;
}
