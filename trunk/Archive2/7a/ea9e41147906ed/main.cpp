#include <tuple>

template<template<typename> class trans> struct no_index_transformer
{
    template<size_t, typename transform_t> struct transformer
    {
        using t = typename trans<transform_t>::t;
    };
};
template<typename, typename> struct tuple_cat;
template<typename... types_one, typename... types_two> struct tuple_cat<std::tuple<types_one...>, std::tuple<types_two...>>
{
public:
    using t = std::tuple<types_one..., types_two...>;
};

template<template<size_t, typename> class transformer, size_t index, typename tuple> class transform_tuple_index;
template<template<size_t, typename> class transformer, size_t index, typename current_t, typename... types> class transform_tuple_index<transformer, index, std::tuple<current_t, types...>>
{
    using current = std::tuple<typename transformer<index, current_t>::t>;
    using next = typename transform_tuple_index<transformer, index + 1, std::tuple<types...>>::t;
    using combined = typename tuple_cat<current, next>::t;
    static constexpr bool test_{ std::is_same<std::tuple<void>, next>::value };

public:
    using t = typename std::conditional<test_, current, combined>::type;
};
template<template<size_t, typename> class transformer, size_t index> class transform_tuple_index<transformer, index, std::tuple<>>
{
public:
    using t = std::tuple<void>;
};


template<template<typename> class transformer, typename tuple> using transform_tuple_t                  
    = typename transform_tuple_index<no_index_transformer<transformer>::template transformer, 0, tuple>::t;

int main() {}