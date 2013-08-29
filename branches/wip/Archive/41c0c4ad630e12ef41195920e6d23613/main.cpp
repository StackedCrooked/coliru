#include <iostream>

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;
#define NAMESPACE(Name) namespace Name { enum IdType { Id }; } namespace Name

NAMESPACE(Foo)
{    
    void process(IdType)
    {
        TRACE
    }
}

NAMESPACE(Bar)
{
    void process(IdType)
    {
        TRACE
    }
}

void initialize() { std::cout << "general init"  << std::endl; }
void finalize  () { std::cout << "general finit\n" << std::endl; }

#define transaction(ID) { initialize(); process((ID)); finalize(); }

int main()
{
    transaction(Foo::Id);
    transaction(Bar::Id);
}