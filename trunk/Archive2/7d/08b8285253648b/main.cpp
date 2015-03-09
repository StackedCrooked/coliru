#include <tuple>

#include<type_traits>

template<typename... Ts> struct List
{
  using Type = List;
};


template<typename List>
struct to_tuple_impl;
template<typename... Ts>
struct to_tuple_impl<List<Ts...>> {
   using Type = std::tuple<Ts...>;
};

template<typename List>
using to_tuple = typename to_tuple_impl<List>::Type;



using List0 = List<>;
using Tuple0=to_tuple<List0>;

static_assert(std::is_same<Tuple0,std::tuple<>>::value, "");


using List2 = List<int,float>;
using Tuple2=to_tuple<List2>;

static_assert(std::is_same<Tuple2,std::tuple<int,float>>::value, "");


int main() {
    return 0;
}