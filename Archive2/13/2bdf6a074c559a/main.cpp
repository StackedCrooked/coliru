#include <iostream>
#include <type_traits>

template <class T> constexpr bool are_same() {return true;} 
template <class T, class U> constexpr bool are_same() {return std::is_same<T, U>::value;} 
template <class T, class U, class... V> 
constexpr typename std::enable_if<sizeof...(V), bool>::type are_same() 
{
    return are_same<T, V...>() && are_same<U, V...>();} 
    
template <class... Ts> typename std::enable_if<are_same<Ts...>()>::type f() {} 

int main() 
{
    f<int, int, int, float>();
}

