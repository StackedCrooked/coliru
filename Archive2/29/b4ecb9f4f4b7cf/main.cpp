#include <boost/type_traits.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/unique.hpp>
#include <boost/mpl/if.hpp>
#include <boost/variant.hpp>

#include <type_traits>
#include <iostream>
#include <utility>

using namespace boost;

/***************************************************************/
// refer http://www.rsdn.ru/forum/cpp/4953155.1
template <typename ...Fs>
struct overload_set;

template<> struct overload_set<> {};

template <typename Head, typename ...Tail>
struct overload_set<Head, Tail...> : Head, overload_set<Tail...>
{
    overload_set(Head head, Tail... tail)
        : Head(head)
        , overload_set<Tail...>(tail...)
    {}

    using Head::operator();
    using overload_set<Tail...>::operator();
};

template <typename F>
struct overload_set<F> : F
{
    overload_set(F f) : F(f) {}

    using F::operator();
};

template <typename ...Fs>
auto overload(Fs... fs)
{
    return overload_set<Fs...>(fs...);
}

template <typename ...Fs>
auto overload(overload_set<>, Fs... fs)
{
    return overload_set<Fs...>(fs...);
}

/***************************************************************/
struct nothing {};

template<typename Overloads, typename T>
struct result_of_overloads
{
    using result = decltype( std::declval<Overloads>()(std::declval<T&>()) );
    using type = typename mpl::if_< boost::is_same<void, result>, nothing, result >::type;
};

template<typename Overloads, typename Types>
struct branches_types
{
    using filtered = typename mpl::transform<Types, result_of_overloads<Overloads, mpl::placeholders::_>>::type;
    using type = typename mpl::unique<filtered, boost::is_same<mpl::placeholders::_, mpl::placeholders::_>>::type;
};

/***************************************************************/
template<typename F, bool enable>
using enable_on_void_return =
    std::enable_if_t<enable == std::is_same<decltype(std::declval<F>()()), void>::value>;

template<typename F>
auto mask_void_result(F &&calc, enable_on_void_return<F, false>* = 0)
{
    return calc();
}

template<typename F>
auto mask_void_result(F &&calc, enable_on_void_return<F, true>* = 0)
{
    calc();
    return nothing{};
}

/***************************************************************/
template<typename ...Fs, typename F>
auto operator*(overload_set<Fs...> fs, F f)
{
    return overload(fs, f);
}

template<typename Result, typename Overloads>
struct visitor
{
    using result_type = Result;
    Overloads overloads;

    template<typename T>
    auto operator()(T &x)
    {
        return mask_void_result([&]{ return overloads(x); });
    }
};

template<typename Variant>
struct match
{
    Variant x;
    template<typename Fs>
    auto operator+(Fs fs)
    {
        using branches = typename branches_types<Fs, typename Variant::types>::type;
        using results_variant = typename make_variant_over<branches>::type;

        visitor<results_variant, Fs> v{fs};
        return apply_visitor(v, x);
    }
};

template<typename Variant>
auto make_match(Variant x)
{
    return match<Variant>{x};
}

/***************************************************************/
#define MATCH(...) make_match(__VA_ARGS__) + overload_set<>{}
#define CASE_AUX(x, type) * [&](type &x)
#define CASE(...) CASE_AUX( __VA_ARGS__ )
#define IS ,
#define _ auto

/***************************************************************/
#define NOINLINE __attribute__ ((noinline))

template<typename ...Ts>
//NOINLINE
auto println(Ts... xs)
{
    using namespace std;
    initializer_list<int>({(cout << xs, 0)...});
    cout << endl;
}
/*
template<typename Variant>
//NOINLINE
auto test(Variant x)
{
    auto y = MATCH(x)
        CASE(x IS int)    { println("int=", x); return 11u; }
        CASE(x IS double) { println("double=", x); return 0.11l; }
        CASE(x IS _)      { println("anything=", x); }
    ;
    MATCH(y)
        CASE(y IS unsigned)    { println("unsigned=", y); }
        CASE(y IS long double) { println("long double=", y); }
        CASE(y IS nothing)     { println("nothing"); }
    ;
    println();
}

int main()
{
    variant<int, double, char> x = 1;
    test(x);
    x = 0.1;
    test(x);
    x = 'a';
    test(x);
}
*/