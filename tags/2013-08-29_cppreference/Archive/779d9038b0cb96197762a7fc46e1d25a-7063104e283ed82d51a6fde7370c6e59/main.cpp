#include <type_traits>

#include <boost/optional/optional.hpp>

/* I rarely go without this for SFINAE purposes */
template<typename...> struct void_ { using type = void; };
template<typename... T> using Void = typename void_<T...>::type;

/* Another classic */
template<typename T> using Unqualified = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

/* as seen in http://flamingdangerzone.com/cxx11/2012/06/01/almost-static-if.html */
template<typename C>
using EnableIf = typename std::enable_if<C::value, int>::type;
template<typename C>
using DisableIf = typename std::enable_if<!C::value, int>::type;

/* Don't use std::result_of */
template<typename Sig, typename Sfinae = void> struct result_of {};
template<typename F, typename... Args>
struct result_of<F(Args...), Void<decltype( std::declval<F>()(std::declval<Args>()...) )>>
{ using type = decltype( std::declval<F>()(std::declval<Args>()...) ); };

template<typename Sig> using ResultOf = typename result_of<Sig>::type;

/*
 * Nullable<T> concept, in the spirit of the Standard NullablePointer
 * concept but relaxed and reduced to a bare minimum. Namely:
 *
 *  - DefaultConstructible<T>, where value-initialized values represent
 *    a null value -- no such requirement on default-constructed values
 *
 *  - Non-null values of T can be dereferenced and t->m is equivalent
 *    to (*t).m
 *
 *  - Values of T are contextually-convertible to bool, where only non-null
 *    values are equal to true
 *
 *  - ValueType<U> represents the type of *std::declval<U>() where T is the
 *    unqualified type of U
 *
 * [ for brevity I only check for operator* ]
 */
template<typename U, typename Sfinae = void>
struct is_dereferenceable: std::false_type {};
    
template<typename U>
struct is_dereferenceable<U, Void<
    decltype(*std::declval<U const&>())
    , decltype(*std::declval<U>())
>>: std::true_type {};

template<typename T>
struct Nullable
: std::integral_constant<
    bool
    , std::is_default_constructible<Unqualified<T>>()
    && is_dereferenceable<Unqualified<T>>()
    && std::is_constructible<bool, Unqualified<T> const&>()
    && std::is_constructible<bool, Unqualified<T>>()
> {};

/* My own ValueType has other purposes beyond e.g. nullable types */
template<typename T>
using ValueType = decltype(*std::declval<T>());

/* Same as ValueType, but with a fallback if the argument does not provide a ValueType */
template<typename T, typename Sfinae = void>
struct safe_value_type { using type = T; };
template<typename T>
struct safe_value_type<T, Void<ValueType<T>>> { using type = ValueType<T>; };

template<typename T> using SafeValueType = typename safe_value_type<T>::type;

/* Associated expression to safe_value_type */
template<typename T, EnableIf<Nullable<T>>...>
ValueType<T> safe_dereference(T&& t) // How 'safe' is it if it always deferences? Hah!
{ return *std::forward<T>(t); }
template<typename T, DisableIf<Nullable<T>>...>
T&& safe_dereference(T&& t) // How 'safe' is it if it forwards an rvalue reference? Hah!
{ return std::forward<T>(t); }

/*
 * Logical conjunction of 'is value non-null?'
 */
bool non_null()
{ return true; }

/* Declare so that next overload see it */
template<typename C, typename... Cs, DisableIf<Nullable<C>>...>
bool non_null(C const& c, Cs const&... cs);

template<typename C, typename... Cs, EnableIf<Nullable<C>>...>
bool non_null(C const& c, Cs const&... cs)
{ return c && non_null(cs...); }

template<typename C, typename... Cs, DisableIf<Nullable<C>>...>
bool non_null(C const& c, Cs const&... cs)
{ return non_null(cs...); }

/* Idiomatic application */
template<typename F,
         typename... Args
         /* I would normally only enable this overload if any of the Args is Nullable */
         >
boost::optional<ResultOf<F(SafeValueType<Args>...)>> apply(F&& f, Args&&... args)
{
    if(non_null(args...)) {
        return std::forward<F>(f)(safe_dereference(std::forward<Args>(args))...);
    } else {
        return {};
    }
}

/* Lifting */
template<typename F>
struct lifted {
    F f;
    
    template<typename... Args>
    auto operator()(Args&&... args)
    -> decltype( apply(f, std::forward<Args>(args)...) )
    { return apply(f, std::forward<Args>(args)...); }
    
    template<typename... Args>
    auto operator()(Args&&... args) const
    -> decltype( apply(f, std::forward<Args>(args)...) )
    { return apply(f, std::forward<Args>(args)...); }
    
    /* Ref-qualified version left as an exercise */
};
template<typename F>
lifted<F> lift(F&& f)
{ return { std::forward<F>(f) }; }

/* Bind-chaining */
template<typename Arg>
Arg with(Arg&& arg)
{
    static_assert( Nullable<Arg>(), "Concept violation" );
    return std::forward<Arg>(arg);
}

template<typename Arg, typename F, typename... Fs>
auto with(Arg&& arg, F&& f, Fs&&... fs)
-> decltype( with(std::forward<F>(f)(*std::forward<Arg>(arg)), std::forward<Fs>(fs)...) )
{
    static_assert( Nullable<Arg>(), "Concept violation" );
    if(arg) {
        return with(std::forward<F>(f)(*std::forward<Arg>(arg)), std::forward<Fs>(fs)...);
    } else {
        return {};
    }
}

#include <cassert>
#include <functional>
#include <sstream>

struct bar {
    int* baz;
};

struct foo {
    bar* b;
};

/* If you must ask... */
template<typename O, typename Ptm>
auto operator->*(O&& o, Ptm ptm)
-> decltype( apply(std::mem_fn(ptm), std::forward<O>(o)) )
{ return apply(std::mem_fn(ptm), std::forward<O>(o)); }

int main()
{
    /* apply demos */
    {
        auto f = [](int i, int j, int k) { return i + j + k; };
        auto o = boost::make_optional(42);
        int five = 5;
        auto r = apply(f, o, &five, 8);
        assert( r && *r == 42 + 5 + 8 );
    }
    /* with some sugar */
    {
        int i = 4;
        bar b { &i };
        foo f { &b };
        boost::optional<foo&> ref = f;
        auto r = ref->*&foo::b->*&bar::baz;
        assert( r && *r == &i );
    }
    
    // You can toy with different inputs here
    // You can also use auto& input = std::cin; at home
    std::istringstream input { "4\n5\n;" };
    
    /* bind-chain demo */
    auto parse_int = [&input]() -> boost::optional<int>
    {
        int i;
        if(input >> i) {
            return i;
        } else {
            return {};
        }
    };
    
    auto result = with(parse_int()
        , lift([](int i) { return 2 * i; })
        , [&parse_int](int i)
        {
            return with(parse_int()
                        , lift([&i](int j) { return i + j; } ));
        }
    );
    
    if(result) {
        std::cout << "Result:\t" << *result << '\n';
    } else {
        std::cout << "No result\n";
    }
}