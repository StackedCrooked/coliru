template <typename... Ts> struct tuple {};
template <typename T, typename... Ts> struct tuple<T, Ts...> : tuple<Ts...> { T head; };
template <bool b, typename T = void> struct enable {};
template <typename T> struct enable<true, T> { using type = T; };
template <typename T, typename U> struct same { static constexpr bool value = false; };
template <typename T> struct same<T, T> { static constexpr bool value = true; };
template <typename T, typename U, typename... Ts> auto get(tuple<U, Ts...>& t) -> typename enable<same<T, U>::value, T>::type& { return t.head; }
template <typename T, typename U, typename... Ts> auto get(tuple<U, Ts...>& t) -> typename enable<!same<T, U>::value, T>::type& { return get<T>(static_cast<tuple<Ts...>&>(t)); }
template <int N, typename T, typename... Ts, typename enable<N == 0>::type* = nullptr> auto& get(tuple<T, Ts...>& t) { return t.head; }
template <int N, typename T, typename... Ts, typename enable<N != 0>::type* = nullptr> auto& get(tuple<T, Ts...>& t) { return get<N - 1>(static_cast<tuple<Ts...>&>(t)); }

#include <iostream>
int main()
{
    std::cout << sizeof(tuple<int>);
}
