#include <iostream>

namespace std {
template< class C > 
auto begin( C& c ) -> decltype(c.begin())
{
    std::cout << "Begin." << std::endl;
    return c.begin();
}

template< class C > 
auto end( C& c ) -> decltype(c.end())
{
    std::cout << "End." << std::endl;
    return c.end();
}
}

int main()
{
    char s[] = "hi there";

    for (char c : s)
        std::cout << c;
        
    return 0;
}