template<typename... T>
struct base {};

template<typename T, typename... Rest>
struct base<T, Rest...> : base<Rest...>
{
    template<typename U, typename... Us>
    U helper(base<U, Us...>*);
    
    template<typename U>
    auto get() -> decltype(this->helper<U>(this));
};

template<typename... Ts>
struct derived : base<Ts...>
{
#if CLANG_FIX
    template<typename U, typename... Us>
    U helper(base<U, Us...>*);
    
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
    
    derived<int, long> d;
    print_type<decltype(d.get<long>())>();
    print_type<decltype(d.get<int>())>();
    
    std::cout << "====================================\n";
}