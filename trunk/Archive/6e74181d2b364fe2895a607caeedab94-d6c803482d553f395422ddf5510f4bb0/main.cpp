#include <tuple>

// Indices as per http://stackoverflow.com/a/7858971/726300
// Very handy when tuples and/or variadic packs are involved
template<int...>
struct indices {};

template<int N, int ...S>
struct generate_indices: generate_indices<N-1, N-1, S...> {};

template<int ...S>
struct generate_indices<0, S...> {
  using type = indices<S...>;
};

template<typename Tuple>
constexpr typename generate_indices<std::tuple_size<typename std::remove_reference<Tuple>::type>::value>::type
indices_for()
{ return {}; }

// std::result_of actually doesn't guarantee this works until C++1y, but some
// C++11 implementations already implement that
template<typename F, typename... Args>
using ResultOf = typename std::result_of<F(Args...)>::type;

// Sfinae helpers
template<typename...> struct void_ { using type = void; };
template<typename... T> using Void = typename void_<T...>::type;

template<typename Cond>
using DisableIf = typename std::enable_if<!Cond::value, int>::type;

// Associated type trait query to ResultOf
template<typename Sfinae, typename F, typename... Args>
struct is_callable_implementation: std::false_type {};

template<typename F, typename... Args>
struct is_callable_implementation<Void<ResultOf<F, Args...>>, F, Args...>
: std::true_type {};

template<typename F, typename... Args>
struct is_callable: is_callable_implementation<void, F, Args...> {};

template<int N, typename Tuple>
using TupleElement = typename std::tuple_element<N, Tuple>::type;

// uncurry(f)(std::make_tuple(3, "hello")) == f(3, "hello")
template<
    typename Functor
    , typename Tuple
    , int... Indices
>
ResultOf<Functor, TupleElement<Indices, Tuple>...> uncurry(Functor&& functor, Tuple&& tuple, indices<Indices...>)
{
    return std::forward<Functor>(functor)(std::get<Indices>(std::forward<Tuple>(tuple))...);
}

template<
    typename Functor
    , typename Tuple
>
auto uncurry(Functor&& functor, Tuple&& tuple)
-> decltype( uncurry(std::forward<Functor>(functor), std::forward<Tuple>(tuple), indices_for<Tuple>()) )
{
    return uncurry(std::forward<Functor>(functor), std::forward<Tuple>(tuple), indices_for<Tuple>());
}

template<typename Functor, typename... Args>
struct curry_type {
    constexpr curry_type(Functor functor, Args... args)
        : functor(std::forward<Functor>(functor))
        , args(std::forward<Args>(args)...)
    {}
    
private:
    Functor functor;
    std::tuple<Args...> args;

    template<typename F, typename... A> friend struct curry_type;
    constexpr curry_type(Functor functor, std::tuple<Args...> args)
        : functor(std::forward<Functor>(functor))
        , args(std::move(args))
    {}

public:
    // Only provide const& qualified overloads for brevity
    
    template<typename... A>
    ResultOf<Functor const&, Args const&..., A...> operator()(A&&... a) const&
    {
        return uncurry(functor, std::tuple_cat(args, std::forward_as_tuple(std::forward<A>(a)...)));
    }

    template<
        typename A
        , typename... As
        , DisableIf<
            is_callable<
                Functor const&
                , Args const&..., A, As...
            >
        >...
    >
    curry_type<Functor const&, Args const&..., A, As...> operator()(A&& a, As&&... as) const&
    {
        return { functor, std::tuple_cat(args, std::forward_as_tuple(std::forward<A>(a), std::forward<As>(as)...)) };
    }
};

template<typename Functor>
curry_type<Functor> curry(Functor&& functor)
{ return { std::forward<Functor>(functor) }; }

#include <iostream>

int main()
{
    auto f = [](const char* p, int i, int j) { return p[2*i + j]; };
    auto c = curry(f);
    
    std::cout << c("Hello, World")(3, 2) << '\n';
    std::cout << std::boolalpha << (c("Hello, World")(3, 2) == f("Hello, World", 3, 2)) << '\n';
}