#include <iostream>
#include <type_traits>

template <typename T>
constexpr decltype(auto) fwd(std::remove_reference_t<T>&& mValue) noexcept
{
    return std::forward<T>(mValue);
}

#if 0 // Require to compile
template <typename T>
constexpr decltype(auto) fwd(std::remove_reference_t<T>& mValue) noexcept
{
    return std::forward<T>(mValue);
}
#endif

template<class T> 
constexpr T&& fwd2(std::remove_reference_t<T>& t) { return std::forward<T>(t); }

template<class T> 
constexpr T&& fwd2(std::remove_reference_t<T>&& t) { return std::forward<T>(t); }


void f(int& ) { std::cout << "l-value ref" << std::endl; }
void f(int&& ) { std::cout << "r-value ref" << std::endl; }

template <typename T> void g_std(T&& t) { f(std::forward<T>(t)); }
template <typename T> void g(T&& t) { f(fwd<T>(t)); }
template <typename T> void g2(T&& t) { f(fwd2<T>(t)); }


int main()
{
    int i;

    g_std(i);
    g_std(42);
    
    g(i); // error: no matching function for call to 'fwd(int&)'
    g(42); // error: no matching function for call to 'fwd(int&)'
    
    g2(i);
    g2(42);
}
