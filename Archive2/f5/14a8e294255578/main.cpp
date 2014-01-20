#include <iostream>
#include <type_traits>

template<bool b, class T = void>
using enable_if_t = typename std::enable_if<b, T>::type;

template<class L, class R>
struct self_check
{
    using type = void;
    static_assert(std::is_same<L, R>::value, "check failed");
};

template<class L>
struct self_check<L, L>
{
    using type = void;
};

template<class L, class R>
using self_check_t = typename self_check<L, R>::type;

class foo
{
    auto ret_self() -> self_check_t<decltype(this), foo*>;
};

class bar
{
    auto ret_self() -> self_check_t<decltype(this), foo*>;
};

int main()
{
    foo f;
}