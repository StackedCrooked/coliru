#include <iostream>
#include <tuple>
using namespace std;

template <typename T>
T random_num() {
    return 0;
}

template<>
int random_num<int>() {
  return 4;   
}

template<>
float random_num<float>() {
  return 4.2f;
}

// Pretending to be lua_State
struct lua {
    
};

// The idea is to build tuples recursively where the types are fixed at compile time
// and the data is loaded dynamically (e.g. the random_num functions).
// So one could write
// auto res = construct<float, int>();
// where res is std::tuple<float, int> with values (4.2f, 4)
template <size_t idx, typename Tup, typename... Args>
struct Builder;

// Append a dynamically generated value to the tuple
template <size_t idx, typename Tup, typename First, typename... Args>
struct Builder<idx, Tup, First, Args...>
{
    
    static First get_num(lua* L) {
        return random_num<First>();   
    }
    
    typedef decltype(std::tuple_cat(std::declval<Tup>(), std::make_tuple(get_num(std::declval<lua*>())))) tuple_combine_t;
    typedef Builder<idx, Tup, First, Args...> current_builder_t;
    typedef Builder<idx + 1, tuple_combine_t, Args...> next_builder_t;
    
    static auto construct(lua* L, Tup t) 
        -> decltype(next_builder_t::construct(L, std::declval<tuple_combine_t>()))
    {
        First n = get_num(L);
        auto next_arg_pack = std::tuple_cat(t, std::make_tuple(n));
        std::cout << idx << "\n";
        return Builder<idx + 1, tuple_combine_t, Args...>::construct(L, next_arg_pack);
    }
    
    typedef decltype(current_builder_t::construct(std::declval<lua*>(), std::declval<Tup>())) return_type;
};

template <size_t idx, typename Tup>
struct Builder<idx, Tup>
{
    static Tup construct(lua* L, Tup args)
    {
        return args;
    }
};

template <typename... Args>
using tuple_builder_start = Builder<2, std::tuple<>, Args...>;

template <typename... Args>
typename tuple_builder_start<Args...>::return_type construct() {
    lua x;
    return tuple_builder_start<Args...>::construct(&x, std::make_tuple());
}

int main() {
    
	// Should be std::tuple<int, float>, (4, 4.2f, 4)
	auto tup = construct<int, float, int>();
    std::cout << std::get<0>(tup) << " " << std::get<1>(tup) << " " << std::get<2>(tup) << "\n";
	return 0;
}