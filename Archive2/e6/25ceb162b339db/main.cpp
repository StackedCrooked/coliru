#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

////////////////////////////////////////////////////////////
// indices

template<std::size_t...>
struct indices {};

template<std::size_t N, std::size_t... Ind>
struct make_indices:
    make_indices<N-1, N-1, Ind...>
{};

template<std::size_t... Ind>
struct make_indices<0, Ind...>:
    indices<Ind...>
{};

////////////////////////////////////////////////////////////
// indice ranges

template<std::size_t C, std::size_t P, std::size_t... N>
struct increasing_indices_range:
    increasing_indices_range<C-1, P+1, N..., P>
{};

template<std::size_t C, std::size_t P, std::size_t... N>
struct decreasing_indices_range:
    decreasing_indices_range<C+1, P-1, N..., P>
{};

template<std::size_t P, std::size_t... N>
struct increasing_indices_range<0, P, N...>:
    indices<N...>
{};

template<std::size_t P, std::size_t... N>
struct decreasing_indices_range<0, P, N...>:
    indices<N...>
{};

template<std::size_t S, std::size_t E, bool Increasing=(S<E)>
struct indices_range;

template<std::size_t S, std::size_t E>
struct indices_range<S, E, true>:
    increasing_indices_range<E-S, S>
{};

template<std::size_t S, std::size_t E>
struct indices_range<S, E, false>:
    decreasing_indices_range<E-S, S>
{};

////////////////////////////////////////////////////////////
// Function traits

template<typename T>
struct function_traits:
    function_traits<decltype(&T::operator())>
{};

template<typename Ret, typename... Args>
struct function_traits<Ret(Args...)>
{
    /**
     * Number of arguments of the function.
     */
    static constexpr std::size_t arity = sizeof...(Args);

    /**
     * Return type of the function.
     */
    using result_type = Ret;

    /**
     * Type of the Nth argument of the function.
     */
    template<std::size_t N>
    using argument_type = typename std::tuple_element<N, std::tuple<Args...>>::type;
};

template<typename Ret, typename... Args>
struct function_traits<Ret(*)(Args...)>:
    function_traits<Ret(Args...)>
{};

template<typename C, typename Ret, typename... Args>
struct function_traits<Ret(C::*)(Args...) const>:
    function_traits<Ret(Args...)>
{};

template<typename T>
struct function_traits<T&>:
    function_traits<T>
{};

template<typename T>
struct function_traits<const T&>:
    function_traits<T>
{};

template<typename T>
struct function_traits<T&&>:
    function_traits<T>
{};

template<typename T>
struct function_traits<const T&&>:
    function_traits<T>
{};

////////////////////////////////////////////////////////////
// curry

template<typename Function, typename First, std::size_t... Ind>
auto curry_impl(const Function& func, First&& first, indices<Ind...>)
    -> std::function<
        typename function_traits<Function>::result_type(
        typename function_traits<Function>::template argument_type<Ind>...)>
{
    return [&](typename function_traits<Function>::template argument_type<Ind>&&... args)
    {
        return func(
            std::forward<First>(first),
            std::forward<typename function_traits<Function>::template argument_type<Ind>>(args)...
        );
    };
}

template<typename Function, typename First,
         typename Indices=indices_range<1, function_traits<Function>::arity>>
auto curry(Function&& func, First first)
    -> decltype(curry_impl(std::forward<Function>(func), std::forward<First>(first), Indices()))
{
    using FirstArg = typename function_traits<Function>::template argument_type<0>;
    static_assert(std::is_convertible<First, FirstArg>::value,
                  "the value to be tied should be convertible to the type of the function's first parameter");
    return curry_impl(std::forward<Function>(func), std::forward<First>(first), Indices());
}

////////////////////////////////////////////////////////////
// compose

template<typename First, typename Second, std::size_t... Ind>
auto compose_impl(const First& first, const Second& second, indices<Ind...>)
    -> std::function<
        typename function_traits<First>::result_type(
        typename function_traits<Second>::template argument_type<Ind>...)>
{
    return [&](typename function_traits<Second>::template argument_type<Ind>&&... args)
    {
        return first(second(
            std::forward<typename function_traits<Second>::template argument_type<Ind>>(args)...
        ));
    };
}

template<typename First, typename Second,
         typename Indices=make_indices<function_traits<Second>::arity>>
auto compose(First&& first, Second&& second)
    -> decltype(compose_impl(std::forward<First>(first), std::forward<Second>(second), Indices()))
{
    static_assert(function_traits<First>::arity == 1u,
                  "all the functions passed to compose, except the last one, must take exactly one parameter");

    using Ret = typename function_traits<Second>::result_type;
    using FirstArg = typename function_traits<First>::template argument_type<0>;
    static_assert(std::is_convertible<Ret, FirstArg>::value,
                  "incompatible return types in compose");

    return compose_impl(std::forward<First>(first), std::forward<Second>(second), Indices());
}

int main()
{
    auto add = [](int a, int b)
    {
        return a + b;
    };
    auto add5 = curry(add, 5);

    auto composed = compose(add5, add);
    std::cout << composed(5, 15) << std::endl;
}
