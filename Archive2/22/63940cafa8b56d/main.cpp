#include <utility>
#include <type_traits>

#define ENABLE_IF(Condition, Type) typename std::enable_if < (Condition), Type>::type

template<std::size_t I = 0, class... Ts>
ENABLE_IF(I == sizeof...(Ts), void) read(int& in, std::tuple<Ts...>& t)
{}

template<std::size_t I = 0, class... Ts>
ENABLE_IF(I < sizeof...(Ts), void) read(int& in, std::tuple<Ts...>& t)
{
    in >> std::get<I>(t);
    read<I + 1>(in, t);
}

int main() {}