#include <tuple>

template <typename T, typename... Args>
struct sumSizeOfArgs {
    enum { totalSize = sizeof(typename std::decay<T>::type) + sumSizeOfArgs<Args...>::totalSize };
};

template<typename T>
struct sumSizeOfArgs<T> {
    enum  {totalSize = sizeof(typename std::decay<T>::type)};
};

template <typename T>
struct function_traits_impl;

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(ClassType::*)(Args...) const>
{
    enum { arity = sizeof...(Args) };
    
    typedef ReturnType result_type;
    
    enum { totalSize = sumSizeOfArgs<Args...>::totalSize };
    
    template <size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
    };
};

template <typename ReturnType, typename... Args>
struct function_traits_impl<ReturnType(Args...)>
{
    enum { arity = sizeof...(Args) };
    
    typedef ReturnType result_type;
    
    enum { totalSize = sumSizeOfArgs<Args...>::totalSize };
    
    template <size_t i>
    struct arg
    {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
    };
};

template <typename T, typename V = void>
struct function_traits : function_traits_impl<T> {};

template <typename T>
struct function_traits<T, decltype((void)&T::operator())> : function_traits_impl<decltype(&T::operator())> {};

int main()
{
    static_assert(function_traits<void(int)>::arity == 1, "!");
    
    auto lambda = [] (int, float) {};
    static_assert(function_traits<decltype(lambda)>::arity == 2, "!");
}
