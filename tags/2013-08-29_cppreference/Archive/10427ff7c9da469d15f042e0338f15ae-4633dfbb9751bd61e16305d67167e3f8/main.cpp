template<class... Ts>
struct make_zero_t{
    template<Ts...>
    struct zero_t{};
};

template<class... Ts>
struct make_zero_tt{
    template<template<Ts...> class TT>
    struct zero_tt{};
};

int main(){
    make_zero_t<>::zero_t<> zt;
    make_zero_tt<>::zero_tt<make_zero_t<>::zero_t> ztt;
}