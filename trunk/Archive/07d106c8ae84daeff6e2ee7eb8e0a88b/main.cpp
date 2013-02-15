#include <iostream>
#include <tuple>
#include <utility>

template <std::size_t ...Is>
struct indices {};

template <typename ...Ts, std::size_t ...Is>
auto
select1(std::tuple<Ts...> t, indices<Is...>) ->
  decltype(std::make_tuple( std::get<Is>(t)... )) {
  return   std::make_tuple( std::get<Is>(t)... );
}

template <typename ...Ts, std::size_t ...Is>
std::tuple<
  typename std::decay<
    typename std::tuple_element<Is,std::tuple<Ts...>>::type
  >::type...
>
select2(std::tuple<Ts...> t, indices<Is...>) {
  return std::make_tuple( std::get<Is>(t)... );
}

static_assert(
 std::is_same<
  decltype(select1(std::declval<std::tuple<int&>>(), indices<0>{})),
  decltype(select2(std::declval<std::tuple<int&>>(), indices<0>{}))>::value,
 "You won't seem me; select1 and select2 decay types."
);

int main() {
  int x;
  std::tuple<int&> t = std::tie(x);
  auto t1 = select1(t, indices<0>{});
  auto t2 = select2(t, indices<0>{});
  return t1!=t2;
}