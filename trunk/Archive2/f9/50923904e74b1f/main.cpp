#include <iostream>
#include <type_traits>

class A {};

template <class T>
struct B_
{

    class type{};

};

template <>
struct B_<int>
{

    using type = A;

};

template <class T>
using B = typename B_<T>::type;

int main()
{
    std::cout << "B<char> " << (std::is_same<B<char>, A>::value ? "==" : "!=") << " A" << std::endl;
    std::cout << "B<int> " << (std::is_same<B<int>, A>::value ? "==" : "!=") << " A" << std::endl;
}