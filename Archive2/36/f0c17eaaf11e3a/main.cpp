#include <iostream>

struct unit
{
};

template<typename T>
struct id
{
    using type = T;
};

struct swallow
{
    template<typename... Args>
    constexpr swallow(Args &&...)
    {
    }
};

namespace tpl
{
    template<typename... Elements>
    struct vector
    {
        static constexpr std::size_t size = sizeof...(Elements);

        template<typename F>
        static unit map(F && f)
        {
            swallow{ (f(id<Elements>{}), 0)... };
            return {};
        }
    };

    namespace _detail
    {
        template<typename TypeVector, typename Function>
        struct _map;
    }

    template<typename Vector, typename Function>
    using map = typename _detail::_map<Vector, Function>::type;

    namespace _detail
    {
        template<typename Vector1, typename Vector2>
        struct _flatten;

        template<typename... Elements1, typename... Elements2>
        struct _flatten<vector<Elements1...>, vector<Elements2...>>
        {
            using type = vector<Elements1..., Elements2...>;
        };
    }

    template<typename Vector1, typename Vector2>
    using flatten = typename _detail::_flatten<Vector1, Vector2>::type;

    namespace _detail
    {
        template<typename Vector, std::size_t N>
        struct _nth;

        template<typename Head, typename... Elements, std::size_t N>
        struct _nth<vector<Head, Elements...>, N>
        {
            static_assert(sizeof...(Elements) + 1 >= N);
            using type = typename _nth<vector<Elements...>, N - 1>::type;
        };

        template<typename Head, typename... Elements>
        struct _nth<vector<Head, Elements...>, 0>
        {
            using type = Head;
        };
    }

    template<typename Vector, std::size_t N>
    using nth = typename _detail::_nth<Vector, N>::type;

    namespace _detail
    {
        template<typename Vector, std::size_t Position, typename Type>
        struct _insert_nth;

        template<typename... Elements, typename Type>
        struct _insert_nth<vector<Elements...>, 0, Type>
        {
            using type = vector<Type, Elements...>;
        };

        template<typename Vector, std::size_t Position, typename Type, bool Inside>
        struct _insert_nth_helper;

        template<typename Head, typename... Elements, std::size_t Position, typename Type>
        struct _insert_nth_helper<vector<Head, Elements...>, Position, Type, true>
        {
            using type = flatten<vector<Head>, typename _insert_nth<vector<Elements...>, Position - 1, Type>::type>;
        };

        template<typename... Elements, std::size_t Position, typename Type>
        struct _insert_nth_helper<vector<Elements...>, Position, Type, false>
        {
            static_assert(Position == sizeof...(Elements));
            using type = vector<Elements..., Type>;
        };

        template<typename... Elements, std::size_t Position, typename Type>
        struct _insert_nth<vector<Elements...>, Position, Type>
        {
            using type = typename _insert_nth_helper<vector<Elements...>, Position, Type, Position < sizeof...(Elements)>::type;
        };

        template<typename Vector, template<typename...> typename Comparator, typename... Elements>
        struct _sorted_insert;

        template<typename Vector, template<typename...> typename Comparator>
        struct _sorted_insert<Vector, Comparator>
        {
            using type = Vector;
        };

        template<template<typename...> typename Comparator, typename Head, typename... Tail>
        struct _sorted_insert<vector<>, Comparator, Head, Tail...>
        {
            using type = typename _sorted_insert<vector<Head>, Comparator, Tail...>::type;
        };

        template<std::size_t Position, std::size_t Begin, std::size_t End, typename Vector, template<typename...> typename Comparator, typename Type>
        struct _sorted_position_impl;

        template<template<typename...> typename Comparator, typename Type>
        struct _sorted_position_impl<0, 0, 0, vector<>, Comparator, Type>
        {
            static constexpr std::size_t value = 0;
        };

        template<typename Single, template<typename...> typename Comparator, typename Type>
        struct _sorted_position_impl<0, 0, 1, vector<Single>, Comparator, Type>
        {
            static constexpr std::size_t value = Comparator<Single, Type>::value;
        };

        template<std::size_t Position, std::size_t Begin, std::size_t End, typename... Elements, template<typename...> typename Comparator, typename Type>
        struct _sorted_position_impl<Position, Begin, End, vector<Elements...>, Comparator, Type>
        {
            static constexpr std::size_t value = Comparator<nth<vector<Elements...>, End - 1>, Type>::value
                ? sizeof...(Elements) // greater than the last element should be placed at the end
                : (Comparator<nth<vector<Elements...>, Position - 1>, Type>::value
                    ? (Comparator<Type, nth<vector<Elements...>, Position>>::value
                        ? Position
                        : _sorted_position_impl<Position + (End - Position) / 2, Position, End, vector<Elements...>, Comparator, Type>::value)
                    : _sorted_position_impl<Position - (Position - Begin) / 2, Begin, Position, vector<Elements...>, Comparator, Type>::value);
        };

        template<typename Vector, template<typename...> typename Comparator, typename Type>
        struct _sorted_position : _sorted_position_impl<Vector::size / 2, 0, Vector::size, Vector, Comparator, Type>
        {
        };

        template<typename... Sorted, template<typename...> typename Comparator, typename Head, typename... Tail>
        struct _sorted_insert<vector<Sorted...>, Comparator, Head, Tail...>
        {
            using type = typename _sorted_insert<typename _insert_nth<vector<Sorted...>, _sorted_position<vector<Sorted...>, Comparator, Head>::value, Head>::type, Comparator, Tail...>::type;
        };

        template<typename... Sorted, template<typename...> typename Comparator>
        struct _sorted_insert<vector<Sorted...>, Comparator>
        {
            using type = vector<Sorted...>;
        };

        template<typename Vector, template<typename...> typename Comparator>
        struct _sort;

        template<typename... Elements, template<typename...> typename Comparator>
        struct _sort<vector<Elements...>, Comparator>
        {
            using type = typename _sorted_insert<vector<>, Comparator, Elements...>::type;
        };
    }

    template<typename Vector, template<typename...> typename Comparator>
    using sort = typename _detail::_sort<Vector, Comparator>::type;
}

struct foo
{
    static constexpr int value = 30;
};

struct bar
{
    static constexpr int value = 15;
};

struct baz
{
    static constexpr int value = 20;
};

struct fizz
{
    static constexpr int value = 10;
};

struct buzz
{
    static constexpr int value = 45;
};

template<typename T, typename U>
struct comparator
{
    static constexpr bool value = T::value < U::value;
};

template<typename T>
void pretty_printer()
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main()
{
    tpl::sort<
        tpl::vector<foo, bar, baz, fizz, buzz>,
        comparator
    >::map([](auto tpl_id){
        std::cout << decltype(tpl_id)::type::value << std::endl;
    });
}
