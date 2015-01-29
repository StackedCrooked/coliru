#include <tuple>

template <typename T>
struct closure_traits : closure_traits<decltype(&T::operator())> {};

#define REM_CTOR(...) __VA_ARGS__
#define SPEC(cv, var, is_var)                                              \
template <typename C, typename R, typename... Args>                        \
struct closure_traits<R (C::*) (Args... REM_CTOR var) cv>                  \
{                                                                          \
    using arity = std::integral_constant<std::size_t, sizeof...(Args) >;   \
    using is_variadic = std::integral_constant<bool, is_var>;              \
    using is_const    = std::is_const<int cv>;                             \
                                                                           \
    using result_type = R;                                                 \
                                                                           \
    template <std::size_t i>                                               \
    using arg = typename std::tuple_element<i, std::tuple<Args...>>::type; \
};

SPEC(const, (,...), 1)
SPEC(const, (), 0)
SPEC(, (,...), 1)
SPEC(, (), 0)


int main()
{
    auto lambda = [](int, ...) mutable {return 0L;};

    using traits = closure_traits<decltype(lambda)>;

    static_assert(std::is_same<long, traits::result_type>{}, "");
    static_assert(std::is_same<int, traits::arg<0>>{}      , "");
    
    static_assert(traits::is_variadic{}, "");
    static_assert(!traits::is_const{}, "");
}