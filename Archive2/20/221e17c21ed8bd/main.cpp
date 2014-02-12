#include <array>

namespace Jarod42 { namespace {
template <typename T, T ... Ts>
inline constexpr std::array<T, sizeof...(Ts)> getArray()
{
    return {{Ts...}};
}

template <typename T, T ... Ts>
inline constexpr T get_argument(size_t index)
{
  return index < sizeof...(Ts) ?
    const_cast<const std::array<T, sizeof...(Ts)>&&>(getArray<T, Ts...>())[index] :
    throw std::out_of_range("Index out of argument range");;
}
}

int test(size_t index) {
    return get_argument<int, 1,2,3,4,5>(index);
}
}

namespace Casey { namespace {
template <typename T, std::size_t N>
struct foo {
    T elements[N];
};

template <typename T, T ... Ts>
constexpr T get_argument(size_t index)
{
  return index < sizeof...(Ts) ?
    foo<T, sizeof...(Ts)>{{Ts...}}.elements[index] :
    throw std::out_of_range("Index out of argument range");;
}
}

int test(size_t index) {
    return get_argument<int, 1,2,3,4,5>(index);
}
}

namespace MadScience { namespace {
template <typename T, T... Args>
struct ArgArray {
    static const T value[sizeof...(Args)];
};
template <typename T, T... Args>
const T ArgArray<T,Args...>::value[sizeof...(Args)] = {Args...};

template <typename T, T ... Ts>
constexpr T get_argument(size_t index)
{
  return index < sizeof...(Ts) ?
    ArgArray<T, Ts...>::value[index] :
    throw std::out_of_range("Index out of argument range");;
}
}

int test(size_t index) {
    return get_argument<int, 1,2,3,4,5>(index);
}
}
