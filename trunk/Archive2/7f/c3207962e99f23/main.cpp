#include <type_traits>

template<typename Condition>
using EnableIf = typename std::enable_if<Condition::value, void>::type;

template<typename T, EnableIf<std::is_arithmetic<T>>...>
void foo(T) {}


int main()
{
    foo(123);
    foo(nullptr);
}