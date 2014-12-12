#include <cstdint>

#include <array>
#include <tuple>
#include <utility>
#include <type_traits>

namespace {
    
using std::make_tuple;
constexpr std::tuple<int64_t, double> data[] = 
{
  make_tuple(1,  5.6),
  make_tuple(2, 10.8),
  make_tuple(3, 20.9)
};

template<typename T, size_t N>
constexpr size_t size(const T(&)[N]) { return N; }

template<typename T, typename...Ts, size_t...Is>
constexpr std::array<T, sizeof...(Is)> get(std::tuple<Ts...> const * data, std::index_sequence<Is...>) {
  return {{ std::get<T>(data[Is])... }};
}

template<typename T, typename...Ts, size_t N>
constexpr decltype(auto) get(const std::tuple<Ts...> (&)[N]) {
  return get<T>(data, std::make_index_sequence<N>());
}

constexpr auto data_1 = get<int64_t>(data);
constexpr auto data_2 = get<double>(data);
constexpr auto data_3 = size(data);
}

#include <iostream>

int main() {
    for(auto&& x : data_1)
        std::cout << x << ',';
    std::cout << std::endl;
    for(auto&& x : data_2)
        std::cout << x << ',';
    std::cout << std::endl;
}