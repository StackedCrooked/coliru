#include <type_traits>
#include <iostream>
#include <typeinfo>
#include <tuple>
#include <algorithm>
#include <utility>
#include <set>

// This type wraps a reference of type X&&
// it then overrides == and < with L and E respectively
template<class X, class L, class E>
struct reorder_ref {
    using ref = reorder_ref;
    X&& x;
    friend bool operator<(ref lhs, ref rhs) {
        return L{}((X&&) lhs.x, (X&&) rhs.x);
    }
    friend bool operator==(ref lhs, ref rhs) {
        return E{}((X&&) lhs.x, (X&&) rhs.x);
    }
    // other comparison ops based off `==` and `<` go here
    friend bool operator!=(ref lhs, ref rhs){return !(lhs==rhs);}
    friend bool operator>(ref lhs, ref rhs){return rhs<lhs;}
    friend bool operator<=(ref lhs, ref rhs){return !(lhs>rhs);}
    friend bool operator>=(ref lhs, ref rhs){return !(lhs<rhs);}
    
    reorder_ref(X&& x_) : x((X&&) x_) {}
    reorder_ref(reorder_ref const&) = default;
};

// a type tag, to pass a type to a function:
template<class X>class tag{using type=X;};

// This type takes a less than and equals stateless functors
// and takes as input a tuple, and builds a tuple of reorder_refs
// basically it uses L and E to compare the elements, but otherwise
// uses std::tuple's lexographic comparison code.
template<class L, class E>
struct reorder_tuple {
    // indexes trick:
    template<class Tuple, class R, size_t... Is>
    R operator()(tag<R>, std::index_sequence<Is...>, Tuple const& in) const {
        // use indexes trick to do conversion
        return R( std::get<Is>(in)... );
    }
    
    // forward to the indexes trick above:
    template<class... Ts, class R=std::tuple<reorder_ref<Ts const&, L, E>...>>
    R operator()(std::tuple<Ts...> const& in) const {
        return (*this)(tag<R>{}, std::index_sequence_for<Ts...>{}, in);
    }
    // pair filter:
    template<class... Ts, class R=std::pair<reorder_ref<Ts const&, L, E>...>>
    R operator()(std::pair<Ts...> const& in) const {
        return (*this)(tag<R>{}, std::index_sequence_for<Ts...>{}, in);
    }
};

// Here is a toy type.  It wraps an int.  By default, it sorts in the usual way
struct Foo {
    int value = 0;
    // usual sort:
    friend bool operator<( Foo lhs, Foo rhs ) {
        return lhs.value<rhs.value;
    }
    friend bool operator==( Foo lhs, Foo rhs ) {
        return lhs.value==rhs.value;
    }
};

// This takes a type-specific ordering stateless function type, and turns
// it into a generic ordering function type
template<template<class...> class order>
struct generic_order {
    template<class T>
    bool operator()(T const& lhs, T const& rhs) const {
        return order<T>{}(lhs, rhs);
    }
};

// Suppose there is a type X for which we have an ordering L
// and we have a map O from Y->X.  This builds an ordering on
// (Y lhs, Y rhs) -> L( O(lhs), O(rhs) ).  We "order" our type
// "by" the projection of our type into another type.  For
// a concrete example, imagine we have an "id" structure with a name
// and age field.  We can write a function "return s.age;" to
// map our id type into ints (age).  If we order by that map,
// then we order the "id" by age.
template<class O, class L = std::less<>>
struct order_by {
    template<class T, class U>
    bool operator()(T&& t, U&& u) const {
        return L{}( O{}((T&&) t), O{}((U&&) u) );
    }
};

// Here is where we build a special order.  Suppose we have a template Z<X> that returns
// a stateless order on type X.  This takes that ordering, and builds an ordering on
// tuples based on it, using the above code as glue:
template<template<class...>class Less, template<class...>class Equals=std::equal_to>
using tuple_order = order_by< reorder_tuple< generic_order<Less>, generic_order<Equals> > >;

// Here is a concrete use of the above
// my_less is a sorting functiont that sorts everything else the usual way
// but it sorts Foo's backwards
template<class T>
struct my_less : std::less<T> {};

// backwards sort:
template<>
struct my_less<Foo> {
    bool operator()(Foo const& lhs, Foo const& rhs) const {
        return rhs.value < lhs.value;
    }
};

using special_order = tuple_order< my_less >;



int main() {
    using test=std::tuple<int, Foo>;
    test a{0,{2}};
    test b{0,{1}};
    
    std::set<test> s1 = {a,b};
    std::set<test, special_order> s2 = {a,b};
    
    std::cout << "s1:\n";
    for(auto x : s1)
        std::cout << std::get<0>(x) << ',' << std::get<1>(x).value << '\n';
    std::cout << "s2:\n";
    for(auto x : s2)
        std::cout << std::get<0>(x) << ',' << std::get<1>(x).value << '\n';
}