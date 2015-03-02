#include <functional>
#include <iostream>
 
template <typename A, typename B, typename U = std::less<int>>
bool f(A a, B b, U u = U())
{
    return u(a, b);
}
 
int main() 
{
    std::cout << std::boolalpha;   
    std::cout << f(5, 20) << '\n';
    std::cout << f(100, 10) << " test" << '\n';
}