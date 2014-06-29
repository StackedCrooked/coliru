#include <cstddef>
#include <tuple>

template<size_t... Ns>
struct indices { typedef indices type; };

template<size_t N, size_t... Ns>
struct build_indices : build_indices<N - 1, N - 1, Ns...> {};

template<size_t... Ns>
struct build_indices<0, Ns...> : indices<Ns...> {};

template<size_t N, size_t... Ns>
struct build_reverse_indices : build_reverse_indices<N - 1, Ns..., N - 1> {};

template<size_t... Ns>
struct build_reverse_indices<0, Ns...> : indices<Ns...> {};

template<typename... Args>
struct types : build_indices<sizeof...(Args)> { typedef types type; };

template<typename TFuncSignature>
struct function_traits;

template<typename T, typename R, typename... Args>
struct function_traits<R(T::*)(Args...)> {
    static const std::size_t arity = sizeof...(Args);
    static const bool is_member_function = true;
    typedef std::tuple<Args...> arg_tuple_type;
    typedef types<Args...> args_type;
    typedef R(T::* function_pointer_type)(Args...);
    typedef typename std::remove_pointer<function_pointer_type>::type function_type;
    typedef R(*free_function_pointer_type)(Args...);
    typedef R return_type;
    template<std::size_t i>
    using arg = typename std::tuple_element<i, arg_tuple_type>::type;
};

template<typename T, typename R, typename... Args>
struct function_traits<R(T::*)(Args...) const> {
    static const std::size_t arity = sizeof...(Args);
    static const bool is_member_function = true;
    typedef std::tuple<Args...> arg_tuple_type;
    typedef types<Args...> args_type;
    typedef R(T::* function_pointer_type)(Args...);
    typedef typename std::remove_pointer<function_pointer_type>::type function_type;
    typedef R(*free_function_pointer_type)(Args...);
    typedef R return_type;
    template<std::size_t i>
    using arg = typename std::tuple_element<i, arg_tuple_type>::type;
};

template<typename R, typename... Args>
struct function_traits<R(Args...)> {
    static const std::size_t arity = sizeof...(Args);
    static const bool is_member_function = false;
    typedef std::tuple<Args...> arg_tuple_type;
    typedef types<Args...> args_type;
    typedef R(function_type)(Args...);
    typedef R(*function_pointer_type)(Args...);
    typedef R(*free_function_pointer_type)(Args...);
    typedef R return_type;
    template<std::size_t i>
    using arg = typename std::tuple_element<i, arg_tuple_type>::type;
};

template<typename R, typename... Args>
struct function_traits<R(*)(Args...)> {
    static const std::size_t arity = sizeof...(Args);
    static const bool is_member_function = false;
    typedef std::tuple<Args...> arg_tuple_type;
    typedef types<Args...> args_type;
    typedef R(function_type)(Args...);
    typedef R(*function_pointer_type)(Args...);
    typedef R(*free_function_pointer_type)(Args...);
    typedef R return_type;
    template<std::size_t i>
    using arg = typename std::tuple_element<i, arg_tuple_type>::type;
};