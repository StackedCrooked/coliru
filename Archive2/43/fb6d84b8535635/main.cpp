#include <iostream>
#include <type_traits>

template<bool B>
class foo
{
    typename std::enable_if<B>::type bar()
    {
        std::cout << "true" << std::endl;
    }
    
    typename std::enable_if<!B>::type bar()
    {
        std::cout << "false" << std::endl;
    }
};

int main()
{
    foo<true> a;
    foo<false> b;
    a.bar();
    b.bar();
}
