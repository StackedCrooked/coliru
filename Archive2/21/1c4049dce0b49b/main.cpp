#include <iostream>
#include <type_traits>

template <typename T>
constexpr decltype(auto) fwd(std::remove_reference_t<T>&& mValue) noexcept
{
    return std::forward<T>(mValue);
}

template <typename T>
constexpr decltype(auto) fwd2(T&& mValue) noexcept
{
    return std::forward<T>(mValue);
}

void f(int& ) { std::cout << "l-value ref" << std::endl; }
void f(int&& ) { std::cout << "r-value ref" << std::endl; }

int main()
{
    int i;

    f(i);
    f(42);
    
    //f(fwd(i));  // error: no matching function for call to 'fwd(int&)'
    //f(fwd(42)); // error: no matching function for call to 'fwd(int)'
    
    f(fwd2(i));
    f(fwd2(42));
}
