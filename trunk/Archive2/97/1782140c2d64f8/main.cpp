#include <iostream>
#include <tuple>
 
template <class T>
void test(T t)
{
    int a[std::tuple_size<T>::value]; // can be used at compile time
 
    std::cout << std::tuple_size<T>::value << '\n'; // or at run time
}
 
int main()
{
    test(std::make_tuple(1, 2, 3.14));
}