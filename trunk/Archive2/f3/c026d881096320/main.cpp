#include <functional>
#include <iostream>
#include <type_traits>

//////////////////////////////////////////
// Indices

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


//////////////////////////////////////////
// Function traits

template<typename T>
struct function_traits:
    function_traits<decltype(&T::operator())>
{};

template<typename C, typename Ret, typename... Args>
struct function_traits<Ret(C::*)(Args...) const>
{
    enum { arity = sizeof...(Args) };

    using result_type = Ret;

    template<std::size_t N>
    using arg = typename std::tuple_element<N, std::tuple<Args...>>::type;
};

//////////////////////////////////////////
// Class Foo

template<typename Ret, typename... Args>
class Foo
{
private:
    std::function<Ret(Args...)> _func;

public:
    Foo(const std::function<Ret(Args...)>& func):
        _func(func)
    {}
    
    auto operator()(Args... args)
        -> Ret
    {
        return _func(args...);
    }
};

//////////////////////////////////////////
// make_foo

template<typename Function, std::size_t... Ind>
auto make_foo_(Function&& func, indices<Ind...>)
    -> Foo<
        typename function_traits<typename std::remove_reference<Function>::type>::result_type,
        typename function_traits<typename std::remove_reference<Function>::type>::template arg<Ind>...>
{
    using Ret = typename function_traits<typename std::remove_reference<Function>::type>::result_type;
    return { std::function<Ret(typename function_traits<typename std::remove_reference<Function>::type>::template arg<Ind>...)>(func) };
}

template<typename Function, typename Indices=make_indices<function_traits<typename std::remove_reference<Function>::type>::arity>>
auto make_foo(Function&& func)
    -> decltype(make_foo_(std::forward<Function>(func), Indices()))
{
    return make_foo_(std::forward<Function>(func), Indices());
}


int main()
{
    auto lambda = [](int i, float b, long c)
    {
        return long(i*10+b+c);
    };

    auto foo = make_foo(lambda);
    std::cout << foo(5, 5.0, 2) << std::endl;
}
