#include <iostream>
#include <sstream>
#include <type_traits>
using std::istream;

template<typename T>
void print(T&&)
{
    std::cout <<
        (std::is_lvalue_reference<T>::value ? "lvalue" : "rvalue") << '\n';
}

template void print<istream&>(istream&);
template void print<istream&&>(istream&&);

int main()
{
    print(std::cin);
    print(std::istringstream{});
}
