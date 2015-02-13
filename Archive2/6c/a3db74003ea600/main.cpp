#include <type_traits>

template<typename...Ts> struct Pack;

template<std::size_t,typename,typename> struct NAppend
{
    using type = void;
};

template<std::size_t N,typename...Ts,typename T>
struct NAppend<N,Pack<Ts...>,T>
{
    using type = typename std::conditional<sizeof...(Ts)==N,void,Pack<Ts...,T>>::type;
};

// filter out all void entries
template<typename,typename U=Pack<>>
struct ShrinkPack
{
    using type = U;
};

template<typename T,typename...Ts,typename...Us>
struct ShrinkPack<Pack<T,Ts...>,Pack<Us...>>
    : std::conditional<
        std::is_void<T>::value,
        ShrinkPack<Pack<Ts...>,Pack<Us...>>,
        ShrinkPack<Pack<Ts...>,Pack<Us...,T>>
    >::type
{
};

// filter out all smaller entries
template<std::size_t,typename,typename U=Pack<>>
struct NPack
{
    using type = U;
};

template<std::size_t N,typename...Ts,typename...Us,typename...Vs>
struct NPack<N,Pack<Pack<Ts...>,Us...>,Pack<Vs...>>
    : std::conditional<
        sizeof...(Ts)==N,
        NPack<N,Pack<Us...>,Pack<Vs...,Pack<Ts...>>>,
        NPack<N,Pack<Us...>,Pack<Vs...>>
    >::type
{
};

template<std::size_t N,typename,typename T=Pack<Pack<>>>
struct NPowerPack
{
    using type = typename NPack<N,T>::type;
};

template<std::size_t N,typename T,typename...Ts,typename...Us>
struct NPowerPack<N,Pack<T,Ts...>,Pack<Us...>>
    : NPowerPack<N,Pack<Ts...>,typename ShrinkPack<Pack<Us...,typename NAppend<N,Us,T>::type...>>::type>
{
};

static_assert(std::is_same<
    NPowerPack<1,Pack<int, char, double>>::type,
    Pack<Pack<int>, Pack<char>, Pack<double>>
>(), "");

static_assert(std::is_same<
    NPowerPack<2,Pack<int, char, double>>::type,
    Pack<Pack<int, char>, Pack<int, double>, Pack<char, double>>
>(), "");

int main() {}
