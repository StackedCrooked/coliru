#include <utility>

// http://coliru.stacked-crooked.com/a/6f45de19a8952f96
#include "concepts.hpp"

/*
  Concept-Lite ==> concepts.hpp
  
    template<typename Type>
    concept bool Fooable =
        is_foo<Type>
        && requires(Type const& x, Type const& y) {
            x.qux(y);
            typename Compute<Type>
            { x + x } -> Compute<Type>
            requires Barable<Compute<Type>>;
            { x * x } -> Barable
        };
    
    Compute<Type> foo(Fooable const& x)
    { return x + x; }
    
    ==>
    
    template<typename Type>
    struct Fooable {
        template<typename X>
        // arity must accept arity of class template, i.e. Fooable has arity 1
        auto requires(X const& x, X const& y = std::declval<X const&>()) -> all_of<
            boolean<is_foo<Type>>,
            expr<decltype( x.qux(y) )>,
            type<Compute<Type>>,
            expr<decltype( x + x ), Compute<Type>>,
            nested<Barable<Compute<Type>>,
            expr<decltype( x * x ), models<Barable>> // WIP
        >;
    };
    
    template<typename Foo, Concepts::Constraints<Fooable<Foo>>...>
    Compute<Foo> foo(Foo const& x)
    { return x + x; }
*/

/* If `foo(x)` results in "no matching function for call to 'foo(...)'", try `foo(Concepts::diagnose(x))` */

/***** Example use *****/
/* None of the following namespacing/organization is mandatory,
 * and is entirely up to preference. E.g. avoiding nested namespaces
 * results in more readable errors.
 *
 * Splitting up concepts in subconcepts yields better diagnostics however.
 */
 
template<typename Val>
constexpr Val const& as_const(Val& val) { return val; }

namespace concepts {

using namespace Concepts;

template<typename Type>
struct ContextualBool {
    template<typename X>
    auto requires(X&& x) -> expr<decltype( std::forward<X>(x) ), explicit_<bool>>; // explicit_ is an extension
};

} // concepts

namespace parts {
    
using namespace Concepts;
    
template<typename Left, typename Right>
struct EqualTo {
    template<typename X, typename Y>
    auto requires(X&& x, Y&& y) -> expr<decltype( as_const(x) == as_const(y) ), models<concepts::ContextualBool>>;
};

template<typename Left, typename Right>
struct NotEqualTo {
    template<typename X, typename Y>
    auto requires(X&& x, Y&& y) -> expr<decltype( as_const(x) != as_const(y) ), models<concepts::ContextualBool>>;
};

template<typename Left, typename Right>
struct LessThan {
    template<typename X, typename Y>
    auto requires(X&& x, Y&& y) -> expr<decltype( as_const(x) < as_const(y) ), models<concepts::ContextualBool>>;
};
    
} // parts

namespace concepts {

template<typename Left, typename Right = Left>
struct EqualityComparable {
    template<typename X, typename Y>
    auto requires(X&& x, Y&& y) -> nested<
        parts::EqualTo<X, Y>,
        parts::EqualTo<Y, X>, // reflexivity
        parts::NotEqualTo<X, Y>,
        parts::NotEqualTo<Y, X>
    >;
};

template<typename Left, typename Right = Left>
struct Comparable {
    template<typename X, typename Y>
    auto requires(X&& x, Y&& y) -> nested<
        EqualityComparable<X, Y>,
        parts::LessThan<X, Y>
    >;
};

} // concepts

template<typename X, typename Y, Concepts::Constraints<concepts::Comparable<X, Y>>...>
auto constrained_function(X&& x, Y&& y)
{ return x < y; }

struct example {};
struct inttable { explicit operator int() const { return 0; } };

bool        operator==(example const&, example const&) { return true; }
// uh oh
inttable    operator!=(example const&, example const&) { return {}; }

int         operator<(example const&, example const&) { return 0; }

int main()
{
    // no matching function for call to 'constrained_function(example, example)'
    // constrained_function(example {}, example {});
    
    // what went wrong?
    constrained_function(Concepts::diagnose(example {}), example {});
}