#include <ostream>
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include <stdexcept>
#include <cassert>

#include <iostream>
#include <string>
#include <utility>
#include <tuple>

/* forward declaration */
template <typename Signature>
struct function_traits;

/* Member function. */
template <typename ReturnType, typename Class, typename... Args>
struct function_traits<ReturnType (Class::*)(Args...)> //: public std::integral_constant<size_t, sizeof...(Args)> {
{
    // arity is the number of arguments.
    static const int arity = (sizeof...(Args));

    using return_type = ReturnType;

    template<size_t i>
    struct arg
    {
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
        using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
    };
};

/* Const member function. */
template <typename ReturnType, typename Class, typename... Args>
struct function_traits<ReturnType (Class::*)(Args...) const> //: public std::integral_constant<size_t, sizeof...(Args)> {
{
  // arity is the number of arguments.
    static const int arity = (sizeof...(Args));

    using return_type = ReturnType;

    template<size_t i>
    struct arg
    {
        // the i-th argument is equivalent to the i-th tuple element of a tuple
        // composed of those arguments.
        using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
    };
};

/* Takes a callable and a list of 0 or more template parameters to specialize the template with. */
template <typename Callable, typename... TemplateArgs>
struct callable_traits;

/* Non-templated operator(). */
template <typename Callable>
struct callable_traits<Callable> : public function_traits<decltype(&Callable::operator())> {};

/* Templated operator(). */
template <typename Callable, typename... TemplateArgs>
struct callable_traits : public function_traits<decltype(&Callable::template operator()<TemplateArgs...>)> {};

/* Convenience type alias for callable_traits<>. */
template <typename Class, typename... TemplateArgs>
using callable_traits_t = callable_traits<Class, TemplateArgs...>;

template<size_t arity, class Callable, typename... TemplateArgs>
struct has_arity : std::integral_constant<
                     bool,
                     callable_traits<Callable, TemplateArgs...>::arity == arity
                  > {};

#include <functional>

namespace std 
{
    template<typename T, T... I>
    struct integer_sequence 
    {
        typedef T value_type;

        static constexpr size_t size() noexcept { return sizeof...(I); }
    };
    
    template<typename T, int N, int... S>
    struct gen_integer_sequence : gen_integer_sequence<T, N-1, N-1, S...>
    {
    };

    template<typename T, int... S>
    struct gen_integer_sequence<T, 0, S...> 
    {
        typedef integer_sequence<T, S...> type;
    };

    template<typename T, T N>
    using make_integer_sequence = typename gen_integer_sequence<T, N>::type;

}  // namespace std

template<typename CALLABLE>
class std_function_convert
{
    private:
        // This function doesn't need a body, it should never be called, and should be hidden internally.
        template<typename T, T... S>
        static auto convert_to_std_function(std::integer_sequence<T, S...>) ->
        std::function<typename callable_traits_t<CALLABLE>::return_type(typename callable_traits_t<CALLABLE>::template arg<S>::type...)>;
    public:
        using type = decltype(convert_to_std_function(typename std::make_integer_sequence<size_t, callable_traits_t<CALLABLE>::arity>()));
};

struct PolyStruct
{
    template<typename T>
    T operator()(T t) { return t; }
};

// test code below:
int main()
{
    auto lambda = [](int i) { return long(i*10); };

    using traits = callable_traits_t<decltype(lambda)>;
    
    static_assert(has_arity<2, decltype(lambda)>::value, "WHAT");
    
    using traits2 = callable_traits_t<PolyStruct, int>;
    static_assert(std::is_same<int, traits2::return_type>::value, "magic");
    static_assert(std::is_same<int, traits2::arg<0>::type>::value, "magic");
    
    using std_function = std_function_convert<decltype(lambda)>::type;
    std_function lf = lambda;
    
    static_assert(std::is_same<std_function, std::function<long(int)>>::value, "err1");
    static_assert(std::is_same<long, traits::return_type>::value, "err2");
    static_assert(std::is_same<int, traits::arg<0>::type>::value, "err3");

    return 0;
}