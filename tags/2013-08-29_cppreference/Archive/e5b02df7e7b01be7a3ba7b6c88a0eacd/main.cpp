#include <iostream>

#define TRACE std::cout << __PRETTY_FUNCTION__ << std::endl;


namespace A
{
    struct id {}; // namespace id type
    
    void process(id = {})
    {
        std::cout << "unikey::def" << std::endl;
    }
}


namespace B
{
    struct id {}; // namespace id type
    
    void process(id = {})
    {
        std::cout << "smartkey::def" << std::endl;
    }
}


namespace C
{
    struct id {}; // namespace id type
    
    void process(id = {})
    {
        std::cout << "superkey::def" << std::endl;
    }
}


void initialize() { std::cout << "general init" << std::endl; }
void finalize()  { std::cout << "general finit" << std::endl << std::endl;; }


template<typename ID>
void transaction(ID id)
{
    initialize();
    process(id);
    finalize();
}


int main()
{
    transaction(A::id());
    transaction(B::id());
    transaction(C::id());
}