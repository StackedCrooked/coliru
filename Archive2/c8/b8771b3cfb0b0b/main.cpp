#include <iostream>

using namespace std;

template<typename D>
struct Base
{
    auto foo()
    -> decltype(this)
    {
        return this;
    }

    void hi()
    {
        std::cout << "Hi";
    }
};

struct Derived: public Base<Derived>
{
    auto foo_impl()
    -> int
    {
        return 0;
    }
};

int main()
{
    Base<int> b;
    b.foo()->hi();
}