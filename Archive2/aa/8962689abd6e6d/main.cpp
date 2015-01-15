#include <iostream>
#include <string>
#include <vector>

struct Base
{
    int x, y;
    Base(int x, int y) : x(x), y(y) { }
    virtual ~Base() { }
    virtual void foo() = 0;
};

struct Derived : public Base
{
    using Base::Base;
    void foo() { }
};

struct Derived2 : public Base
{
    using Base::Base;
    void foo() { }    
};

struct Derived3 : public Base
{
    using Base::Base;
    void foo() { }    
};

template <typename A, typename B,
    typename = typename std::enable_if<std::is_base_of<Base, A>::value && std::is_base_of<Base, B>::value>::type>
A operator-(const A& a, const B& b)
{
    return {b.x - a.x, b.y - a.y};
}

struct NotDerived1 { };
struct NotDerived2 { };

int main()
{
    Derived d1{1, 2};
    Derived2 d2{3, 2};
    d1 = d1 - d2;
    std::cout << d1.x << " " << d1.y;
    NotDerived1 nd1;
    NotDerived2 nd2;
    nd1 = nd1 - nd2;
}
