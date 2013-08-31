#include<tuple>
#include<utility>

template <std::size_t ...Is>
struct indices {};

template <typename ...Ts, std::size_t ...Is>
auto
select1(std::tuple<Ts...> t, indices<Is...>) ->
  decltype(std::make_tuple( std::get<Is>(t)... )) {
  return   std::make_tuple( std::get<Is>(t)... );
}

template <typename ...Ts, std::size_t ...Is>
std::tuple<typename std::tuple_element<Is,std::tuple<Ts...>>::type...>
select2(std::tuple<Ts...> t, indices<Is...>) {
  return std::make_tuple( std::get<Is>(t)... );
}

static_assert(std::is_same<decltype(select1(std::declval<std::tuple<int&>>(), indices<0>{})), std::tuple<int>>::value, "make_tuple decays types");
static_assert(std::is_same<decltype(select2(std::declval<std::tuple<int&>>(), indices<0>{})), std::tuple<int&>>::value, "tuple_element does not decay types");

int main() {
    int x;
    std::tuple<int&> t = std::tie(t);
    auto t1 select1(t, indices<0>{});
    auto t2 select2(t, indices<0>{});
}

