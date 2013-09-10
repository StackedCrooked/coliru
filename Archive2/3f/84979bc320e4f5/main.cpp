#include <type_traits>

template <typename T>
struct enable_if_t : std::enable_if<T::value, int> {};
template <typename T>
struct disable_if_t : std::enable_if<!T::value, int> {};

template <typename T>
using EnableIf = typename enable_if_t<T>::type;

template <typename T>
using DisableIf = typename disable_if_t<T>::type;

template <typename T,
          EnableIf<std::is_integral<T>> = 0>
void f(T) {}

template <typename T,
          DisableIf<std::is_integral<T>> = 0>
void f(T);

int main()
{
    f(0);
}
