template<int X, typename... T>
struct base {};

template<int X, typename T, typename... Rest>
struct base<X, T, Rest...> : base<X+1, Rest...>
{
    template<typename U, int Y, typename... Us>
    U helper(base<Y, U, Us...>*);
    
    template<typename U>
    auto get() -> decltype(this->helper<U>(this));
};

template<int X, typename... Ts>
struct derived : base<X, Ts...>
{
#if CLANG_FIX
    template<typename U, int Y, typename... Us>
    U helper(base<Y, U, Us...>*);
    
    template<typename U>
    auto get() -> decltype(this->helper<U>(this));
#endif
};

#include <iostream>
template<typename T>
void print_type() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

int main()
{
    std::cout << "CLANG_FIX = " << CLANG_FIX << "\n";
    
    derived<0, int, long> d;
    print_type<decltype(d.get<long>())>();
    print_type<decltype(d.get<int>())>();
    
    std::cout << "====================================\n";
}