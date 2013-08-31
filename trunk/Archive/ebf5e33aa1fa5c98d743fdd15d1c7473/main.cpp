#include <iostream>

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


namespace A
{    
    void process()
    {
        std::cout << "unikey::def" << std::endl;
    }
}


namespace B
{    
    void process()
    {
        std::cout << "smartkey::def" << std::endl;
    }
}


namespace C
{    
    void process()
    {
        std::cout << "superkey::def" << std::endl;
    }
}


void initialize() { std::cout << "general initialization" << std::endl; }
void finalize()  { std::cout << "general finalization" << std::endl << std::endl;; }


template<typename ID>
void transaction(ID id)
{
    initialize();
    process(id);
    finalize();
}


// Inject id types into the namespaces.
namespace A { struct id {}; void process(id) { process(); } }
namespace B { struct id {}; void process(id) { process(); } }
namespace C { struct id {}; void process(id) { process(); } }


int main()
{
    transaction(A::id());
    transaction(B::id());
    transaction(C::id());
}