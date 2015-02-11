#include <type_traits>

template<typename...Ts> struct Pack;

template<typename,typename> struct Append;

template<typename...Ts,typename T>
struct Append<Pack<Ts...>,T>
{
    using type = Pack<Ts...,T>;
};

template<typename T,typename> struct Explode
{
    using type = T;
};

template<typename...Ts,typename U,typename...Us>
struct Explode<Pack<Ts...>,Pack<U,Us...>>
    : Explode<Pack<Ts...,typename Append<Ts,U>::type...>,Pack<Us...>>
{
};

template<typename T>
using PowerPack = typename Explode<Pack<Pack<>>,T>::type;

static_assert(std::is_same<
    PowerPack<Pack<int, char, double>>,
    Pack<Pack<>, Pack<int>, Pack<char>, Pack<int, char>, Pack<double>, Pack<int, double>, Pack<char, double>, Pack<int, char, double>>
>(), "");

int main() {}
