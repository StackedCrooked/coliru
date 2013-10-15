#include <iostream>

class base
{
protected:
    void test()
    {
        std::cout << "base::test()\n";
    }
};

class derived : protected base
{
public:
    using base::test;
};

int main()
{
    derived d;

    d.test(); // ok
    // d.base::test(); // compile error
}
