template <typename... Ts> struct tuple {};
template <typename T, typename... Ts> struct tuple<T, Ts...> : tuple<Ts...> { T head; };
template <typename T, typename U> struct same {};
template <typename T> struct same<T, T> { using type = T; };
template <typename T, typename U> struct not_same { using type = T; };
template <typename T> struct not_same<T, T> {};
template <typename T, typename U, typename... Ts>
auto get(tuple<U, Ts...>& t) -> typename same<T, U>::type& { return t.head; }
template <typename T, typename U, typename... Ts>
auto get(tuple<U, Ts...>& t) -> typename not_same<T, U>::type& { return get<T>(static_cast<tuple<Ts...>&>(t)); }

#include <iostream>
int main()
{
    tuple<int, char, float> t;    
    get<int>(t) = 123;
    get<char>(t) = 'a';
    get<float>(t) = 3.14f;
    
    std::cout << get<int>(t) << std::endl;
    std::cout << get<char>(t) << std::endl;
    std::cout << get<float>(t) << std::endl;
}
