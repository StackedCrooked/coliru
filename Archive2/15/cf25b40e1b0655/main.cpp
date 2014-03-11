#include <type_traits>
#include <utility>


template<typename T>
inline auto Max(const T& a, const T& b) -> T
{
    return b < a ? a : b;
}


template<typename A, typename B>
inline auto Max(const A& a, const B& b) -> typename std::common_type<A, B>::type
{
    typedef typename std::common_type<A, B>::type R;
    return Max(static_cast<R>(a), static_cast<R>(b));
}

template<typename First, typename Second, typename ...Tail>
inline auto Max(const First& first, const Second& second, Tail&& ...tail) -> typename std::common_type<First, Second, Tail...>::type
{
    return Max(Max(first, second), std::forward<Tail>(tail)...);
}


template<typename T>
inline auto Min(const T& a, const T& b) -> T
{
    return b < a ? b : a;
}


template<typename A, typename B>
inline auto Min(const A& a, const B& b) -> typename std::common_type<A, B>::type
{
    typedef typename std::common_type<A, B>::type R;
    return Min(static_cast<R>(a), static_cast<R>(b));
}

template<typename First, typename Second, typename ...Tail>
inline auto Min(const First& first, const Second& second, Tail&& ...tail) -> typename std::common_type<First, Second, Tail...>::type
{
    return Min(Min(first, second), std::forward<Tail>(tail)...);
}


#include <iostream> 

int main()
{
    
    std::cout << Min(1, 2);
    std::cout << Min(2, 1);
    std::cout << std::endl;
    
    std::cout << Min(1, 2, 3);
    std::cout << Min(1, 3, 2u);
    std::cout << Min(2, 1l, 3);
    std::cout << Min(2, 3, 1);
    std::cout << Min(3, 1, 2);
    std::cout << Min(3, 2, 1);
    std::cout << std::endl;
    
    std::cout << Min(1, 1, 2, 3);
    std::cout << Min(1, 1, 3, 2);
    std::cout << Min(1, 2u, 1, 3);
    std::cout << Min(1, 2, 3, 1l);
    std::cout << Min(1, 3, 1, 2);
    std::cout << Min(1, 3, 2, 1);
    std::cout << Min(2, 1, 2, 3);
    std::cout << Min(2, 1, 3, 2);
    std::cout << Min(2, 2, 1, 3);
    std::cout << Min(2, 2, 3, 1);
    std::cout << Min(2, 3, 1, 2);
    std::cout << Min(2, 3, 2, 1);        
    std::cout << Min(3, 1, 2, 3);
    std::cout << Min(3, 1, 3, 2);
    std::cout << Min(3, 2, 1, 3);
    std::cout << Min(3, 2, 3, 1);
    std::cout << Min(3, 3, 1, 2);
    std::cout << Min(3, 3, 2, 1);
    std::cout << std::endl;
    
    
    
    std::cout << Max(1, 2);
    std::cout << Max(2, 1);
    std::cout << std::endl;
    
    std::cout << Max(1, 2, 3);
    std::cout << Max(1, 3, 2u);
    std::cout << Max(2, 1l, 3);
    std::cout << Max(2, 3, 1);
    std::cout << Max(3, 1, 2);
    std::cout << Max(3, 2, 1);
    std::cout << std::endl;
    
    std::cout << Max(1, 1, 2, 3);
    std::cout << Max(1, 1, 3, 2);
    std::cout << Max(1, 2u, 1, 3);
    std::cout << Max(1, 2, 3, 1l);
    std::cout << Max(1, 3, 1, 2);
    std::cout << Max(1, 3, 2, 1);        
    std::cout << Max(2, 1, 2, 3);
    std::cout << Max(2, 1, 3, 2);
    std::cout << Max(2, 2, 1, 3);
    std::cout << Max(2, 2, 3, 1);
    std::cout << Max(2, 3, 1, 2);
    std::cout << Max(2, 3, 2, 1);        
    std::cout << Max(3, 1, 2, 3);
    std::cout << Max(3, 1, 3, 2);
    std::cout << Max(3, 2, 1, 3);
    std::cout << Max(3, 2, 3, 1);
    std::cout << Max(3, 3, 1, 2);
    std::cout << Max(3, 3, 2, 1);
    std::cout << std::endl;
    
}