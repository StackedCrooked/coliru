#include <iostream>
 
template<class... Args>
std::size_t f()
{
    return sizeof...(Args);
}
 
int main()
{
    std::cout << f<>() << '\n'
              << f<int>() << '\n'
              << f<char, int>() << '\n';
}