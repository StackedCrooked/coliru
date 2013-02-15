#include <type_traits>

namespace my {
    template <typename Func>
    struct result_of {};
    template <typename Fun, typename... Args>
    struct result_of<Fun(Args...)> : std::result_of<Fun(Args...)> {};
}

template<typename Func>
typename my::result_of<Func&()>::type foo(Func f)
{ return f(); }

template<typename Func>
typename my::result_of<Func&(int)>::type foo(Func f)
{ return f(42); }

int main()
{
    foo([](int) {});
}