#include <cstdlib>
#include <tuple>
#include <utility>

template<size_t i, typename... args_t>
struct for_each_impl
{
    using this_type = typename std::tuple_element<i, std::tuple<args_t...>>::type;

    using prev_type = for_each_impl<i - 1, args_t...>;

    template<template<typename> class func_t>
    using instantiate = typename func_t<this_type>::type;
    //Note: I stripped recursion here to keep it simple
};

template<typename... args_t>
struct for_each_impl<0, args_t...>
{
    using this_type = typename std::tuple_element<0, std::tuple<args_t...>>::type;

    template<template<typename> class func_t>
    using instantiate = typename func_t<this_type>::type;
};

template<typename... args_t>
struct for_each
{
    using prev_type = for_each_impl<sizeof...(args_t) - 1, args_t...>;

    template<template<typename> class func_t>
    using instantiate = 
        typename prev_type::instantiate<func_t>; // <<--- error
};

int main(int argc, char** argv)
{
    return 0;
}