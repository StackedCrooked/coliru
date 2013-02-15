#include <iostream>

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;
#define NAMESPACE(Name) namespace Name { enum Id {}; } namespace Name

NAMESPACE(Foo)
{    
    void process(Id = {})
    {
        TRACE
    }
}

NAMESPACE(Bar)
{
    void process(Id = {})
    {
        TRACE
    }
}

void initialize() { std::cout << "general init"  << std::endl; }
void finalize  () { std::cout << "general finit\n" << std::endl; }


template<typename Id>
void transaction(Id id = {})
{
    initialize();
    process(id);
    finalize();
}

typedef Foo::Id TargetId;
static const TargetId cTargetId{};

int main()
{
    transaction(cTargetId);
}