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
struct qualifying: identity<Qualifee> {};

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
    
    template<typename... Tuples>
    friend auto tuple_cat(Tuples&&... tuples)
    -> decltype( std::tuple_cat(as_base::forward<Tuples>(tuples)...) )
    { return std::tuple_cat(as_base::forward<Tuples>(tuples)...); }
};

int main()
{
    data d { 42, "swordfish" };
    data e { 69, "bananana" };
    // Using std::move because the unfinished qualifying is only correct for rvalues lol
    return std::get<0>(tuple_cat(std::move(d), std::move(e), std::make_tuple(3, 4, 5.)));
}