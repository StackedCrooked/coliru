#include <boost/variant.hpp>
#include <iostream>
//...
template <typename T1, typename T2>
auto Bigger(T1 a1, T2 a2) -> boost::variant<T1, T2>
{
   if(a2 > a1) return a2; else return a1;
   // or just return a2 > a1 ? a2 : a1;
}

int main()
{
    std::cout << Bigger(10, 'c');
}