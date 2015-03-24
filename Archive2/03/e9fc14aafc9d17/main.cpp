#include <tuple>
#include <boost/tuple/tuple.hpp>
#include <utility>
#include <type_traits>
#include <string>
#include <cassert>
template <typename StdTuple, std::size_t... Is>
auto asBoostTuple(StdTuple&& stdTuple, std::index_sequence<Is...>) {
    return boost::tuple<std::tuple_element_t<Is, std::decay_t<StdTuple>>...>(std::get<Is>(std::forward<StdTuple>(stdTuple))...);
}

template <typename BoostTuple, std::size_t... Is>
auto asStdTuple(BoostTuple&& boostTuple, std::index_sequence<Is...>) {
    return std::tuple<typename boost::tuples::element<Is, std::decay_t<BoostTuple>>::type...>(boost::get<Is>(std::forward<BoostTuple>(boostTuple))...);
}

template <typename StdTuple>
auto asBoostTuple(StdTuple&& stdTuple) {
  return asBoostTuple(std::forward<StdTuple>(stdTuple), std::make_index_sequence<std::tuple_size<std::decay_t<StdTuple>>::value>());
}

template <typename BoostTuple>
auto asStdTuple(BoostTuple&& boostTuple) {
  return asStdTuple(std::forward<BoostTuple>(boostTuple), std::make_index_sequence<boost::tuples::length<std::decay_t<BoostTuple>>::value>());
}

int main() {
  boost::tuple<std::string, int, char> x = asBoostTuple(std::make_tuple("A", 1, 'x'));
  std::tuple<std::string, int, char> y = asStdTuple(x);
  assert(boost::get<0>(x) == "A");
  assert(boost::get<1>(x) == 1);
  assert(boost::get<2>(x) == 'x');
  assert(std::get<0>(y) == "A");
  assert(std::get<1>(y) == 1);
  assert(std::get<2>(y) == 'x');
  return 0;
}
