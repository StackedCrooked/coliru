#include <functional>
#include <type_traits>
#include <iostream>

/* The usual stuff */

template<typename T>
using EnableIf = typename std::enable_if<T::value, int>::type;

template<typename...>
struct void_ { using type = void; };

template<typename... T>
using Void = typename void_<T...>::type;

namespace detail {
    
template<typename Sfinae, typename F, typename R, typename... Args>
struct is_callable_impl: std::false_type {};

template<typename F, typename R, typename... Args>
struct is_callable_impl<Void<decltype( std::declval<F>()(std::declval<Args>()...) )>, F, R, Args...>
: std::integral_constant<
    bool
    , std::is_convertible<decltype( std::declval<F>()(std::declval<Args>()...) ), R>::value
    || std::is_void<decltype( std::declval<F>()(std::declval<Args>()...) )>::value
> {};

} // detail

template<typename F, typename R, typename... Args>
struct is_callable: detail::is_callable_impl<void, F, R, Args...> {};

/* Okay now done with the preparations */

namespace crummy {
    
void deleter_a(int)
{ std::cout << "crummy deleter_a\n"; }
void deleter_b(int, int*)
{ std::cout << "crummy deleter_b\n"; }

} // crummy

// This is just easier to work with:

struct deleter_a {
    void operator()(int i) const
    { crummy::deleter_a(i); }
};

struct deleter_b {
    void operator()(int i, int* p) const
    { crummy::deleter_b(i, p); }
};

namespace detail {
    
struct addressof {
    template<typename T>
    constexpr T* operator()(T& t)
    { return std::addressof(t); }
};
    
} // detail

template<typename Deleter>
struct holder_type {
    holder_type(int id, Deleter deleter)
        : id(id)
        , deleter(std::forward<Deleter>(deleter))
    {}
    
    ~holder_type() noexcept
    {
        try {
            deleter(id);
        } catch(...) {}
    }
    
private:
    int id;
    Deleter deleter;
};

template<typename Deleter, EnableIf<is_callable<Deleter&, void, int&>>...>
holder_type<typename std::decay<Deleter>::type> holder(int id, Deleter&& deleter)
{
    return { id, std::forward<Deleter>(deleter) };
}

template<typename Deleter, EnableIf<is_callable<Deleter&, void, int, int*>>...>
auto holder(int id, Deleter&& deleter)
-> decltype( holder(id, std::bind(std::forward<Deleter>(deleter), 1, std::bind(detail::addressof {}, std::placeholders::_1))) )
{ return holder(id, std::bind(std::forward<Deleter>(deleter), 1, std::bind(detail::addressof {}, std::placeholders::_1))); }

// How to make it convenient to embed a holder_type:

template<typename Deleter>
using Holder = decltype( holder(0, std::declval<Deleter>()) );

struct foo {
    Holder<deleter_a> h;
};

struct bar {
    Holder<deleter_b> h;
};

int main()
{
    foo f { holder(42, deleter_a {}) };
    bar b { holder(33, deleter_b {}) };
}