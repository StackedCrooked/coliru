#include <tuple>

template <typename T>
struct closure_traits : closure_traits<decltype(&T::operator())> {};

#define REM_CTOR(...) __VA_ARGS__
#define SPEC(cv, var, is_var)                                              \
template <typename C, typename R, typename... Args>                        \
struct closure_traits<R (C::*) (Args... REM_CTOR var) cv>                  \
{                                                                          \
    static constexpr auto arity = sizeof...(Args);                         \
    static constexpr auto is_variadic = is_var;                            \
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
    auto lambda = [](int i, ...) mutable { return long(i*10); };

    typedef closure_traits<decltype(lambda)> traits;

    static_assert(std::is_same<long, traits::result_type>::value, "err");
    static_assert(std::is_same<int, traits::arg<0>>::value, "err");
    
    static_assert(traits::is_variadic, "err");
}