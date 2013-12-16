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

template <typename ReturnType, typename... Args>
struct function_traits<ReturnType(Args..., ...)> //: public std::integral_constant<size_t, sizeof...(Args)> {
{
    // arity is the number of arguments.
    static const int arity = (sizeof...(Args));
    
    using return_type = ReturnType;

    template<size_t i>
    using arg = typename std::tuple_element<i, std::tuple<Args...>>::type;
};

template <typename ReturnType>
struct function_traits<ReturnType(...)> //: public std::integral_constant<size_t, sizeof...(Args)> {
{
    static const int arity = 0;
    using return_type = ReturnType;
};

/* Member function. */
template <typename ReturnType, typename Class, typename... Args>
struct function_traits<ReturnType (Class::*)(Args...)> //: public std::integral_constant<size_t, sizeof...(Args)> {
{
    // arity is the number of arguments.
    static const int arity = (sizeof...(Args));

    using return_type = ReturnType;

    template<size_t i>
    using arg = typename std::tuple_element<i, std::tuple<Args...>>::type;
};

/* Const member function. */
template <typename ReturnType, typename Class, typename... Args>
struct function_traits<ReturnType (Class::*)(Args...) const> //: public std::integral_constant<size_t, sizeof...(Args)> {
{
  // arity is the number of arguments.
    static const int arity = (sizeof...(Args));

    using return_type = ReturnType;

    template<size_t i>
    using arg = typename std::tuple_element<i, std::tuple<Args...>>::type;
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

void func(const int, ...)
{
}

// test code below:
int main()
{
    static_assert(std::is_same<std::return_type<decltype(func)>, void>::value == true, "is same");
    
    std::cout << function_traits<decltype(func)>::arity << std::endl;
    static_assert(std::is_const<function_traits<decltype(func)>::arg<0>>::value == false, "is the same thing!");
    return 0;
}