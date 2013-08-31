#include <boost/variant.hpp>

template<typename ...CRT>
struct foo : 
{
    template<typename C>
    foo(C && c) : var(std::forward<C>(c)) {}
    
    void test()
    {
        
    }
    
    boost::variant<CRT...> var;
};

struct bar : foo<bar> {};

int main(){}