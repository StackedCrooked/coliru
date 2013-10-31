#include <array>
#include <type_traits>
#include <iostream>

template<std::size_t...> struct seq {};

template<typename,typename> struct cat;
template<std::size_t... Is, std::size_t... Js>
struct cat<seq<Is...>,seq<Js...>>
{
    using type = seq<Is...,Js...>;
};

template<typename> struct extract_seq { using type = seq<>; };
template<typename T,std::size_t N>
struct extract_seq<T[N]>
{
    using type = typename cat<seq<N>,typename extract_seq<T>::type>::type;
};

template<typename T> struct extract_type { using type = T; };
template<typename T,std::size_t N>
struct extract_type<T[N]>
  : extract_type<T>
{};

template<typename,typename> struct to_array_helper;
template<typename T, std::size_t... Is>
struct to_array_helper<T,seq<Is...>>
{
    constexpr static const std::array<T,sizeof...(Is)> value {{ Is... }};
};

template<typename T, std::size_t... Is>
constexpr const std::array<T,sizeof...(Is)>
to_array_helper<T,seq<Is...>>::value;

template<typename T>
struct to_array
  : to_array_helper<typename extract_type<T>::type,
                    typename extract_seq<T>::type>
{};

int main()
{
    constexpr const auto arr = to_array< int[1][2][3] >::value;
    for( auto v : arr ) std::cout << v << " ";
}
