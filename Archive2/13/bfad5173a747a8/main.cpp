#include <iostream>
#include <type_traits>
#include <boost/any.hpp>

template <size_t, typename...>
struct select_type { };

template <size_t index, typename First, typename... Types>
struct select_type<index, First, Types...> : public select_type<index - 1, Types...> { };

template <typename First, typename... Types>
struct select_type<0, First, Types...>
{
    using type = First;
};

template <typename T>
struct function_traits : public function_traits<decltype(&T::operator())> { };

template <typename Return, typename Class, typename... Args>
struct function_traits<Return (Class::*)(Args...) const>
{
    using result_type = Return;

    template <size_t argN>
    using argument_type = select_type<argN, Args...>;
};

template <typename... Functors>
struct any_call_impl
{
    static bool call(boost::any &, Functors const & ...)
    {
        return false;
    }

    static bool call(boost::any const &, Functors const & ...)
    {
        return false;
    }
};

template <typename FirstFunctor, typename... Functors>
struct any_call_impl<FirstFunctor, Functors...>
{
    static bool call(boost::any & v, FirstFunctor const & first, Functors const & ... rest)
    {
        using arg = typename function_traits<FirstFunctor>::template argument_type<0>::type;
        using arg_bare = typename std::remove_cv<typename std::remove_reference<arg>::type>::type;

        if (v.type() == typeid(arg_bare)) {
            first(*boost::any_cast<arg_bare>(&v));
            return true;
        }

        return any_call_impl<Functors...>::call(v, rest...);
    }

    static bool call(boost::any const & v, FirstFunctor const & first, Functors const & ... rest)
    {
        using arg = typename function_traits<FirstFunctor>::template argument_type<0>::type;
        using arg_bare = typename std::remove_cv<typename std::remove_reference<arg>::type>::type;

        if (v.type() == typeid(arg_bare)) {
            first(*boost::any_cast<arg_bare>(&v));
            return true;
        }

        return any_call_impl<Functors...>::call(v, rest...);
    }
};

template <typename... Functors>
bool any_call(boost::any & v, Functors const & ... f)
{
    return any_call_impl<Functors...>::call(v, f...);
}

template <typename... Functors>
bool any_call(boost::any const & v, Functors const & ... f)
{
    return any_call_impl<Functors...>::call(v, f...);
}

int main(void) {
    boost::any a = 1;

    any_call(a,
        [](double d) { std::cout << "double " << d << std::endl; },
        [](int i) { std::cout << "int " << i << std::endl; }
    );

    return 0;
}
