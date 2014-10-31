#include <utility>

/*constexpr std::size_t index_seq_to_index(std::index_sequence<>, std::index_sequence<>, std::size_t const entries)
{
    return 0;
}

template<std::size_t Dimension, std::size_t... Dimensions, std::size_t Index, std::size_t... Indices>
constexpr std::size_t index_seq_to_index(std::index_sequence<Dimension, Dimensions...>, std::index_sequence<Index, Indices...>, std::size_t const entries)
{
    return Index * entries/Dimension + index_seq_to_index(std::index_sequence<Dimensions...>, std::index_sequence<Indices...>, entries/Dimension);
}*/

template<std::size_t, typename>
struct append_t;

template<std::size_t New, std::size_t... List>
struct append_t< New, std::index_sequence<List...> >
{
    using type = std::index_sequence<List..., New>;
};

template<std::size_t N, typename L>
using append = typename append_t<N, L>::type;

template<std::size_t Index, std::size_t... Dimensions>
struct index_seq_from_index_t
{
    using type = std::index_sequence<>;
};

template<std::size_t Index, std::size_t Dimension, std::size_t... Dimensions>
struct index_seq_from_index_t<Index, Dimension, Dimensions...>
{
    using type = append< Index%Dimension, typename index_seq_from_index_t<Index/Dimension, Dimensions...>::type >;
};

template<std::size_t Index, std::size_t... Dimensions>
using index_seq_from_index = typename index_seq_from_index_t<Index, Dimensions...>::type;

#include <iostream>
#include <array>

template<class T>
void print_type() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

template <typename T, int FIRST, int... REST>
struct NArray
{
    using type = std::array<typename NArray<T, REST...>::type, FIRST>;
};

template <typename T, int N>
struct NArray<T, N> {
    using type = std::array<T, N>;
};

constexpr std::size_t multiply() { return 1; }

template<class... Rest>
constexpr std::size_t multiply(std::size_t first, Rest... rest)
{
    return first * multiply(rest...);
}

template<typename T, std::size_t... Dimensions, std::size_t... Indices, typename Initializer>
constexpr auto get_initialized_array(std::index_sequence<Indices...>, Initializer&& initializer)
{
    return typename NArray<T, Dimensions...>::type{ std::forward<Initializer>(initializer)(index_seq_from_index<Indices, Dimensions...>{})... };
}

template<typename T, typename... Packs>
struct Initializer
{
    T const& data;
    constexpr T const& operator()(...) const { return data; }
    
    constexpr Initializer(T const& def) : data(def) {}
};
template<typename T, typename Pack, typename... Packs>
struct Initializer<T, Pack, Packs...> : Initializer<T, Packs...>
{
    Pack data;
    constexpr T operator()(typename Pack::indices) { return data; }
    using Initializer<T, Packs...>::operator();
    
    constexpr Initializer(T const& def, Pack data, Packs... rest) : Initializer<T, Packs...>(def, std::move(rest)...), data(std::move(data)) {}
};

template<typename T, std::size_t... Dimensions, typename... Packs>
constexpr auto get_initialized_array(T const& def, Packs... packs)
{
    return get_initialized_array<bool, Dimensions...>(std::make_index_sequence<multiply(Dimensions...)>{}, Initializer<T, Packs...>{def, std::move(packs)...});
}

template<typename T, std::size_t... Indices>
struct pack
{
    T t;
    
    using indices = std::index_sequence<Indices...>;
    
    template<typename U>
    operator U() { return std::move(t); }
};

template<std::size_t... Indices, typename T>
pack<T&&, Indices...> make_pack(T&& t)
{
    return {std::forward<T>(t)};
}

int main()
{
    auto const arr = get_initialized_array<bool, 5, 3>(false, make_pack<2,0>(true));
    print_type<decltype(arr)>();
    for(auto const& e : arr)
        for(auto const& f : e)
            std::cout << f << ", ";
}