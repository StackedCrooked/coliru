#include <iostream>
#include <functional>

namespace detail
{
    template <typename F>
    struct function_traits
      : public function_traits<decltype(&F::operator())>
    { };
     
    template <typename C, typename R, typename... Args>
    struct function_traits<R (C::*)(Args...) const>
    {
      using type = std::function<R (Args...)>;
    };
     
    template <typename C, typename R, typename... Args>
    struct function_traits<R (C::*)(Args...)>
    {
      using type = std::function<R (Args...)>;
    };
}

template <typename... Args>
void work(std::function<Args...> const &)
{ std::cout << "working" << std::endl; }

template <typename... Args>
void foo(std::function<Args...> const &f)
{ work(f); }

template <typename L>
void foo(L const &lam)
{
    auto const func(typename detail::function_traits<L>::type{ lam });
    work(func);
}

int main()
{
    foo([]{});
}
