#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
#include <boost/type_erasure/callable.hpp>
#include <boost/type_erasure/any_cast.hpp>
#include <boost/type_erasure/derived.hpp>
#include <boost/type_erasure/call.hpp>
#include <boost/type_erasure/any.hpp>
#include <initializer_list>
#include <iostream>
#include <type_traits>
#include <vector>

using namespace std;
using namespace boost;
using namespace type_erasure;

/***************************************/
template<typename T = _self>
struct implicitly_convertable
{
    static T &apply(T &x) { return x; }
};

namespace boost { namespace type_erasure {
    template<typename C, typename Base>
    struct concept_interface<implicitly_convertable<C>, Base, C> : Base
    {
        template<typename T> operator T()
        {
            return any_cast<T>(*static_cast<typename derived<Base>::type*>(this));
        }
    };
}}

template<typename ...Concepts>
using regular_any = any<mpl::vector<copy_constructible<>, relaxed, typeid_<>, Concepts...>>;
template<typename ...Singatures>
using any_func = regular_any< callable<Singatures>... >;;

using value = regular_any< implicitly_convertable<> >;


/***************************************/
template<typename T = _self>
struct arbitrary_callable
{
    struct No{};
    struct A{}; struct B : A{};
    
    template<typename X, typename ...Args>
    static No call(X &x, const A&, Args...) { throw 's';}
        
    template<typename X, typename ...Args>
    static auto call(X &x, const B&, Args... args) -> decltype(x(args...)) { return x(args...);}

    static value apply(T &x, vector<value> args)
    {
        static_assert
        (
            (!std::is_same<No, decltype(call(x, B{}, args[0]))>::value) ||
            (!std::is_same<No, decltype(call(x, B{}, args[0], args[1]))>::value)
            , "do not has right version" );
        if(args.size() == 1)
            return call(x, B{}, args[0]);
        if(args.size() == 2)
            return call(x, B{}, args[0], args[1]);
        throw 11.;
    }
};

namespace boost { namespace type_erasure {
    template<typename C, typename Base>
    struct concept_interface<arbitrary_callable<C>, Base, C> : Base
    {
        template<typename ...Args>
        auto operator()(Args... args)
        {
            return call(arbitrary_callable<C>(), *this, vector<value>{ args... });
            //any_cast<T>(*static_cast<typename derived<Base>::type*>(this));
        }
    };
}}
/***************************************/

//using func = any_func< value(value) >;
using func = regular_any< arbitrary_callable<> >;
using higher_order_func = any_func< value(func) >;

struct X
{
    value operator()(func f)
    {
        return f(11);
    }
} x;

struct Y
{
    value operator()(func f)
    {
        return f(11, 22);
    }
} y;

value apply(higher_order_func f, func g)
{
    return f(g);
}

int sum(int x, int y)
{
    return x + y;
}

int square(int x)
{
    return x * x;
}

struct NonCallable {};

int main()
{
    int res = apply(x, square);
    cout << res << endl;
    res = apply(y, sum);
    cout << res << endl;
    //apply(y, NonCallable{}); // compile error
}