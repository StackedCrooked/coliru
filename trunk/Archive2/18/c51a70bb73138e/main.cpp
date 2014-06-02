#include <cstddef>
#include <type_traits>
#include <utility>

template <class... Ts>
struct tuple;

template <class T, class... Ts>
struct tuple<T, Ts...>
{
    T first;
    tuple<Ts...> rest;
    
    tuple() = default;
    template <class U, class...Us, class=typename ::std::enable_if<!::std::is_base_of<tuple,typename ::std::decay<U>::type>::value>::type>
    tuple(U&& u, Us&&...tail) :
      first(::std::forward<U>(u)),
      rest(::std::forward<Us>(tail)...) {}
};

template <class T>
struct tuple<T>
{
    T first;

    tuple() = default;
    template <class U, class=typename ::std::enable_if<!::std::is_base_of<tuple,typename ::std::decay<U>::type>::value>::type>
    tuple(U&& u) :
      first(::std::forward<U>(u)) {}
};

template <>
struct tuple<> {};

namespace detail {

    template < ::std::size_t i, class T>
    struct tuple_element;

    template < ::std::size_t i, class T, class... Ts>
    struct tuple_element<i, tuple<T, Ts...> >
        : tuple_element<i - 1, tuple<Ts...> >
    {};

    template <class T, class... Ts>
    struct tuple_element<0, tuple<T, Ts...> >
    {
        using type = T;
    };


    template < ::std::size_t i>
    struct tuple_accessor
    {
        template <class... Ts>
        static inline typename tuple_element<i, tuple<Ts...> >::type & get (tuple<Ts...> & t)
        {
            return tuple_accessor<i - 1>::get(t.rest);
        }

        template <class... Ts>
        static inline const typename tuple_element<i, tuple<Ts...> >::type & get (const tuple<Ts...> & t)
        {
            return tuple_accessor<i - 1>::get(t.rest);
        }
    };

    template <>
    struct tuple_accessor<0>
    {
        template <class... Ts>
        static inline typename tuple_element<0, tuple<Ts...> >::type & get (tuple<Ts...> & t)
        {
            return t.first;
        }

        template <class... Ts>
        static inline const typename tuple_element<0, tuple<Ts...> >::type & get (const tuple<Ts...> & t)
        {
            return t.first;
        }
    };

} // namespace detail



template <class... Ts>
inline tuple<typename ::std::decay<Ts>::type...> make_tuple (Ts &&... x)
{
    return tuple<typename ::std::decay<Ts>::type...>(::std::forward<Ts>(x)...);
}

template < ::std::size_t i, class... Ts>
inline typename detail::tuple_element<i, tuple<Ts...> >::type & get (tuple<Ts...> & t)
{
    return detail::tuple_accessor<i>::get(t);
}

template < ::std::size_t i, class... Ts>
inline const typename detail::tuple_element<i, tuple<Ts...> >::type & get (const tuple<Ts...> & t)
{
    return detail::tuple_accessor<i>::get(t);
}



static_assert(::std::is_standard_layout<tuple<bool, int, float, char, double, tuple<int, char> > >(), "Compiler is stupid");

#include <cassert>
#include <string>
int main() {
    using type = tuple<int, double, ::std::string>;
    type t(42, 3.14, "Jabberwocky is killing user.");
    type u;
    u = t;
    t = std::move(u);
    type v = t;
    assert(get<0>(v) == 42);
    assert(get<1>(v) == 3.14);
    assert(get<2>(v) == "Jabberwocky is killing user.");
}
