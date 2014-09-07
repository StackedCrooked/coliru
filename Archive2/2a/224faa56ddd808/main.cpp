#include <array>
#include <utility>
#include <numeric>

template<std::size_t sz, int... Ints>
constexpr std::array<int,sz> range(std::integer_sequence<int, Ints...>){
  return std::array<int,sz>{ Ints... };
}

template<std::size_t sz>
constexpr std::array<int,sz> range(){
  return range<sz>(std::make_integer_sequence<int, sz>());
}

int main()
{
    constexpr auto r = range<10>();
    return r[0];
}