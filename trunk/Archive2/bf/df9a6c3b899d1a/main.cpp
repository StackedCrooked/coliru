#include <tuple>

template <typename T, typename... Args>
struct sumSizeOfArgs
{
    static constexpr size_t totalSize = sizeof(typename std::decay<T>::type) + sumSizeOfArgs<Args...>::totalSize;
};

template <typename T>
struct sumSizeOfArgs<T>
{
    static constexpr size_t totalSize = sizeof(typename std::decay<T>::type);
};

template <typename T>
struct function_traits_impl;

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(ClassType::*)(Args...)>
{
    static constexpr size_t arity = sizeof...(Args);
    
    using result_type = ReturnType;
    
    static constexpr size_t totalSize = sumSizeOfArgs<Args...>::totalSize;
    
    template <size_t i>
    struct arg
    {
        using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
    };
};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(ClassType::*)(Args...) const>
    : function_traits_impl<ReturnType(ClassType::*)(Args...)> {};

template <typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(Args...)>
{
    static constexpr size_t arity = sizeof...(Args);
    
    using result_type = ReturnType;
    
    static constexpr size_t totalSize = sumSizeOfArgs<Args...>::totalSize;
    
    template <size_t i>
    struct arg
    {
        using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
    };
};

template <typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(*)(Args...)> : function_traits_impl<ReturnType(Args...)> {};

template <typename T, typename V = void>
struct function_traits : function_traits_impl<T> {};

template <typename T>
struct function_traits<T, decltype((void)&T::operator())> : function_traits_impl<decltype(&T::operator())> {};

int main()
{
    static_assert(function_traits<void(int)>::arity == 1, "!");
    
    static_assert(function_traits<void(*)(int, float)>::arity == 2, "!");  
    
    auto lambda = [] (int, float) {};
    static_assert(function_traits<decltype(lambda)>::arity == 2, "!");
    
    auto mutable_lambda = [] (int, float, char) mutable {};
    static_assert(function_traits<decltype(mutable_lambda)>::arity == 3, "!");
}
