template<unsigned... values> struct range
{
    template<template<unsigned...> class T>
    struct apply
    {
        typedef T<values...> type;
    };
};

template<unsigned x, typename vector> struct push_front;
template<unsigned x, unsigned... values>
struct push_front<x, range<values...>>
{
    typedef range<x, values...> type;
};

template<unsigned n, typename vector = range<>>
struct iota
{
    typedef typename iota
    <
        n-1, typename push_front<n-1, vector>::type
    >::type type;
};

template<typename vector>
struct iota<0, vector>
{
    typedef vector type;
};

template<typename> void type_is();

int main()
{
    type_is<iota<5>::type>();
}
