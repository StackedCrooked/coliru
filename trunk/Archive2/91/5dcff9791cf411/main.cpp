#include <type_traits>

template<typename Condition>
using EnableIf = typename std::enable_if<Condition::value, void>::type;

template<typename T, typename...> struct depend { using type = T; };
template<typename T, typename... Dependees> using depend_t = typename depend<T, Dependees...>::type;

template<typename T, typename... U>
void foo(T, EnableIf<std::is_arithmetic<depend_t<T, U>>>*...) {}


int main()
{
    foo(123);
    foo(nullptr);
    
    foo<int*, int>(0, nullptr);
}