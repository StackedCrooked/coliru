#include <utility>
#include <type_traits>

/* The usual stuff */

template<typename T> struct identity { using type = T; };

template<typename If, typename Then, typename Else>
using LazyConditional = typename std::conditional<If::value, Then, Else>::type::type;

template<typename T>
using Unqualified = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

template<typename T, typename U>
struct is_related: std::is_same<Unqualified<T>, Unqualified<U>> {};

// Too lazy to implement properly, let's pretend it is
template<typename Qualifier, typename Qualifee>
struct qualifying
: std::conditional<std::is_lvalue_reference<Qualifier>::value, typename std::remove_reference<Qualifee>::type&, Qualifee> {};

/* The interesting stuff */

template<typename Derived>
class as_base {
    template<typename T>
    struct base_type
    : qualifying<T, typename Unqualified<T>::base_type> {};
    
    template<typename T>
    using BaseType = LazyConditional<
        is_related<T, Derived>
        , base_type<T>
        , identity<T>
    >;
    
protected:
    template<typename T>
    static BaseType<T>&& forward(T& t)
    { return std::forward<T>(t); }
};

#include <tuple>
#include <string>

struct data: private std::tuple<int, std::string>, as_base<data> {
private:
    using base_type = std::tuple<int, std::string>;
    using base_type::tuple;
    friend class as_base<data>;
    
    template<int I, typename Self>
    friend auto get(Self&& self)
    -> decltype( std::get<I>(data::as_base::forward<Self>(self)) )
    { return std::get<I>(self); }
    
    template<typename... Tuples>
    friend auto tuple_cat(Tuples&&... tuples)
    -> decltype( std::tuple_cat(data::as_base::forward<Tuples>(tuples)...) )
    { return std::tuple_cat(data::as_base::forward<Tuples>(tuples)...); }
};

template<int I, typename Self>
auto get(Self const& self)
-> decltype( std::get<I>(data::as_base::forward<Self const&>(self)) );

template<typename... Tuples>
auto tuple_cat(Tuples&&... tuples)
-> decltype( std::tuple_cat(data::as_base::forward<Tuples>(tuples)...) );

#include <cassert>

int main()
{
    data d { 42, "swordfish" };
    data e { 69, "bananana" };
    assert( get<1>(d) == "swordfish" );
    
    // Using std::move because the unfinished qualifying is only correct for rvalues here lol
    auto r = std::get<0>(tuple_cat(std::move(d), std::move(e), std::make_tuple(3, 4, 5.)));
    assert( r == 42 );
}