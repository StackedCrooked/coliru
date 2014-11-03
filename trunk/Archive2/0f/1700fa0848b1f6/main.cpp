#include <stack>
#include <iostream>

struct Dummy
{
    Dummy() {}    
    Dummy(Dummy&) { std::cout << "Dummy(Dummy&)" << std::endl; }
    Dummy(const Dummy&) { std::cout << "Dummy(const Dummy&)" << std::endl; }
};

int main()
{
    std::stack<Dummy> s;
    Dummy dummy;
    s.push(dummy);   // (1)
    s.emplace(dummy);   // (2)
}
