#include <type_traits>

template<typename...Ts> struct Pack;

template<typename,typename> struct Append;

template<typename...Ts,typename T>
struct Append<Pack<Ts...>,T>
{
    using type = Pack<Ts...,T>;
};

template<typename,typename T=Pack<Pack<>>>
struct PowerPack
{
    using type = T;
};

template<typename T,typename...Ts,typename...Us>
struct PowerPack<Pack<T,Ts...>,Pack<Us...>>
    : PowerPack<Pack<Ts...>,Pack<Us...,typename Append<Us,T>::type...>>
{
};

static_assert(std::is_same<
    PowerPack<Pack<int, char, double>>::type,
    Pack<Pack<>, Pack<int>, Pack<char>, Pack<int, char>, Pack<double>, Pack<int, double>, Pack<char, double>, Pack<int, char, double>>
>(), "");

int main() {}
