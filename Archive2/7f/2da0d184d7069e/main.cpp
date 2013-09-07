#include <type_traits>
#include <utility>

/* Logical conjunction */

template<typename... Conds>
struct all: std::true_type {};

template<typename C, typename... Cs>
struct all<C, Cs...>: std::integral_constant<bool, C::value && all<Cs...>::value> {};

template<typename... Conds>
using All = typename all<Conds...>::type;

/* SFINAE utilities */
template<typename Cond>
using EnableIf = typename std::enable_if<Cond::value, int>::type;

template<typename...>
struct void_ { using type = void; };

template<typename... T>
using Void = typename void_<T...>::type;


/* For things that are barely concepts, but more syntactic requirements */
namespace op {
    
// Helpers to reduce the std::declval noise
template<typename T> T& lvalue();
template<typename T> T const& clvalue();

template<typename T, typename Sfinae = void>
struct EqualityComparable: std::false_type {};

template<typename T>
struct EqualityComparable<T, Void<decltype( clvalue<T>() == clvalue<T>(), clvalue<T>() != clvalue<T>() )>>
: All<
    std::is_convertible<decltype( clvalue<T>() == clvalue<T>() ), bool>
    , std::is_convertible<decltype( clvalue<T>() != clvalue<T>() ), bool>
> {};

template<typename T, typename Sfinae = void>
struct LvalueSwappable: std::false_type {};

using std::swap;

template<typename T>
struct LvalueSwappable<T, Void<decltype( swap(lvalue<T>(), lvalue<T>()) )>>
: std::true_type {};

template<typename T, typename Sfinae = void>
struct NullptrComparable: std::false_type {};

template<typename T>
struct NullptrComparable<T, Void<decltype( clvalue<T>() == nullptr, nullptr == clvalue<T>(), clvalue<T>() != nullptr, nullptr != clvalue<T>() )>>
: All<
    std::is_convertible<decltype(clvalue<T>() == nullptr ), bool>
    , std::is_convertible<decltype( nullptr == clvalue<T>() ), bool>
    , std::is_convertible<decltype( clvalue<T>() != nullptr ), bool>
    , std::is_convertible<decltype( nullptr != clvalue<T>() ), bool>
> {};

template<typename T, typename Sfinae = void>
struct Dereferenceable: std::false_type {};

template<typename T>
struct Dereferenceable<T, Void<decltype( *lvalue<T>() )>>
: std::true_type {};

template<typename T, typename Sfinae = void>
struct Preincrementable: std::false_type {};

template<typename T>
struct Preincrementable<T, Void<decltype( ++lvalue<T>() )>>
: std::is_convertible<decltype( ++lvalue<T>() ), T&> {};

} // op

/* 17.6.3.3 NullablePointer requirements */
template<typename T>
struct NullablePointer: All<
    std::is_default_constructible<T>
    , std::is_copy_constructible<T>
    , std::is_copy_assignable<T>
    , std::is_destructible<T>
    , op::EqualityComparable<T>
    , op::LvalueSwappable<T>
    , op::NullptrComparable<T>
    , std::is_constructible<T, std::nullptr_t>
    , std::is_convertible< std::nullptr_t, T>
    , std::is_constructible<bool, T const&>
> {};


/* 24.2.2 Iterator */
template<typename T>
struct Iterator: All<
    std::is_copy_constructible<T>
    , std::is_copy_assignable<T>
    , std::is_destructible<T>
    , op::LvalueSwappable<T>
    , op::Dereferenceable<T>
    , op::Preincrementable<T>
> {};

#include <memory>
#include <cassert>
#include <iterator>

template<typename P, EnableIf<NullablePointer<P>>...>
int foo(P&) { return 0; }

template<typename It, EnableIf<Iterator<It>>...>
int foo(It&) { return 1; }

int main()
{
    std::shared_ptr<int> p;
    assert( foo(p) == 0 );
    
    std::istream_iterator<int> it;
    assert( foo(it) == 1 );
    
    int* q;
    assert( foo(q) == -1 );
}