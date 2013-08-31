#include <iostream>

template<typename ...Arg>
auto apply(Arg && ...arg) -> decltype(arg...)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return arg;
}

template<typename ...Args>
void foo(Args && ...args)
{
    apply<Args>(args)... ;
}

int main()
{
    foo(1, false, 'c');
}