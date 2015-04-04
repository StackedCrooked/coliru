#include <iostream>
#include <type_traits>

template<bool B>
class foo
{
    typename std::enable_if<B>::type bar()
    {
        std::cout << "bar";
    }
    
    typename std::enable_if<!B>::type bar()
    {
        std::cout << "baz";
    }
};

int main()
{
    foo<true> a;
}
