#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

class A
{
public:
    A() : m_value(0) {}
    
    A(const A& a)
        : m_value(a.m_value)
    {
        std::cout << "ctor" << '\n';
    }
    
    A(A&& a)
        : m_value(a.m_value)
    {
        std::cout << "move" << '\n';
    }
    
    A& operator=(const A&)
    {
        std::cout << "copy assign" << '\n';
        return *this;
    }
    
    A& operator=(A&&)
    {
        std::cout << "move assign" << '\n';
        return *this;
    }
    
    void increment()
    {
        ++m_value;
    }
    
int m_value;
};

A f()
{
    A a;
    a.increment();
    
    return a;
}
 
int main()
{
    auto x = f();
    
    std::cout << x.m_value << '\n';
}