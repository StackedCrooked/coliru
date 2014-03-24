#include <type_traits>
#include <vector>
#include <iostream>
 
template <size_t N>
void fun(const int (&a)[N])
{
    std::cout << "Array overload: ";
    for (int n: a)
        std::cout << n << ' ';
    std::cout << '\n';
}
 
void fun(const std::vector<int>& v)
{
    std::cout << "Vector overload: ";
    for (int n: v)
        std::cout << n << ' ';
    std::cout << '\n';
}
 
int main()
{
    fun( {1, 2, 3} ); // calls the vector overload
    fun( std::common_type<int[]>::type {1, 2, 3} ); // calls the array overload
}