#include <iostream>
#include <utility>
#include <type_traits>

int foo()
{
    return 0;
}

template<typename T>
void check(T)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    using foo_type = decltype(&foo);
    check(foo_type{});
    
    using result_type = typename std::result_of<foo_type>::type;
    check(result_type{});
}