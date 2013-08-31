#include <iostream>

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;
#define NAMESPACE(Name) namespace Name { enum Identify {}; } namespace Name

NAMESPACE(Foo)
{    
    void process(Identify = 0)
    {
        TRACE
    }
}

NAMESPACE(Bar)
{
    void process(Identify = 0)
    {
        TRACE
    }
}

void initialize() { std::cout << "general init"  << std::endl; }
void finalize  () { std::cout << "general finit\n" << std::endl; }

#define transaction(ID) { initialize(); process((ID)); finalize(); }

int main()
{
    transaction(Foo::Identify());    
    transaction(Bar::Identify());
}