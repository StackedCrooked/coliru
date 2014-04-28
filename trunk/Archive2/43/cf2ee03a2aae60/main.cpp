#include <iostream>
#include <iostream>
#include <map>
#include <set>


struct Foo
{
    int x;
};

class A
{
public:
    A() : m_foos([](auto f1, auto f2){ return f1.x < f2.x; })
    {
    }
private:
    std::set<Foo, bool(*)(const Foo&, const Foo&)> m_foos;
};


int main() {
    
}