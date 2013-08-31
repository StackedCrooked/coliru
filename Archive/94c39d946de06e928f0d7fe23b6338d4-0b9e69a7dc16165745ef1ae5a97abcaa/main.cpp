#include <iostream>

namespace A
{
    struct Helper
    {
        Helper(int n) : n(-n) {}
        operator int() { return n; }        
        int n;
    };    
    
    template<typename T>
    auto f(T n)
    {
        return Helper(n);
    }
}


namespace B
{
    template<typename T>
    auto f(T n)
    {
        struct Helper
        {
            Helper(int n) : n(-n) {}
            operator int() { return n; }
            int n;
        };
        return Helper(n);
    }    
}




int main()
{
    {
        using namespace A;
        std::cout << f(f(42)) << std::endl;
    }
    
    {
        using namespace B;
        std::cout << f(f(42)) << std::endl;
    }
}