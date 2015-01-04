#include <iostream>

template<typename T>
class Parent
{
protected:
    virtual int Show()
    {
        std::cout<<"Parent::Show Called\n";
        return 0;
    }
};

class Child : Parent<Child>
{
protected:
    virtual int Show() final override
    {
        std::cout<<"Child::Show Called\n";

        auto call_parent = [&] {
            Parent<Child>::Show();
        };
        call_parent();
        return 0;
    }
public:
    void f() { Show(); }
};

int main()
{
    Child c;
    c.f();
}