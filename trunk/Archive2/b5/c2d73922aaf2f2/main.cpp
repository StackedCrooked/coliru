#include <iostream>
#include <string>
#include <typeinfo>

struct named
{
    virtual ~named() = default ;
    virtual std::string name() const { return typeid(*this).name() ; }
};

namespace Detail { struct IntermediateClass : named {}; }

class FinalClass : public named {} ;

int main()
{
    Detail::IntermediateClass ic ;
    FinalClass fc ;
    std::cout << ic.name() << "    " << fc.name() << '\n' ;
}