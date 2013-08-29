#include <type_traits>
#include <utility>
#include <cstddef>
#include <tuple>

// A quick implementation of n3658 "Compile-time integer sequences".

template<typename T, T... I>
struct integer_sequence
{
    using value_type = T;
    static constexpr std::size_t size() noexcept
    { return sizeof...(I); }

    using next = integer_sequence<T, I..., size()>;
};

template<typename T> struct identity { using type = T; };

template<typename T, T N, typename Sfinae = void>
struct make_integer_sequence_impl
: identity<typename make_integer_sequence_impl<T, N - 1>::type::next> {};

template<typename T, T N>
struct make_integer_sequence_impl<T, N, typename std::enable_if<N == 0>::type>
: identity<integer_sequence<T>> {};

template<typename T, T N>
using make_integer_sequence = typename make_integer_sequence_impl<T, N>::type;

// Implementation of fix proper

// Put in namespace for ADL-enabled get
namespace ns {

// Holds one functor out of several that are mutually recursive
template<typename Derived, int I, typename F>
struct fix_holder {
    F functor;

    template<typename... Args>
    decltype(auto) operator()(Args&&... args) &
    { return functor(static_cast<Derived&>(*this), std::forward<Args>(args)...); }

    template<typename... Args>
    decltype(auto) operator()(Args&&... args) const&
    { return functor(static_cast<Derived const&>(*this), std::forward<Args>(args)...); }

    template<typename... Args>
    decltype(auto) operator()(Args&&... args) &&
    { return std::move(functor)(static_cast<Derived&&>(*this), std::forward<Args>(args)...); }

    // By making the construction/assignment operation protected, we ensure that only
    // a derived class can construct holders and thus the downcasts should be safe.
protected:
    explicit fix_holder(F functor): functor(std::forward<F>(functor)) {}
    fix_holder(fix_holder const&) = default;
    fix_holder& operator=(fix_holder const&) = default;
    fix_holder(fix_holder&&) = default;
    fix_holder& operator=(fix_holder&&) = default;
};

/*
 * A tuple-like holder of mutually-recursive functors. Use of ADL get<N>(f) permits fetching
 * of one 'element' to call it individually, although it is not possible to construct/copy/move
 * such an element. Instead the whole tuple-like fix_type must be copied/moved
 * all in one go. This is necessary as the mutually recursive functors should not be separated from
 * one another.
 */
template<typename Sequence, typename... Fs> struct fix_type;

template<int... I, typename... Fs>
struct fix_type<integer_sequence<int, I...>, Fs...>
: public fix_holder<fix_type<integer_sequence<int, I...>, Fs...>, I, Fs>... {
    using self_type = fix_type;

    fix_type(Fs... fs): fix_holder<self_type, I, Fs>(std::forward<Fs>(fs))... {}

    template<std::size_t N>
    using Nth = typename std::tuple_element<N, std::tuple<Fs...>>::type;

    template<std::size_t N>
    friend fix_holder<self_type, N, Nth<N>>& get(self_type& self) { return self; }

    template<std::size_t N>
    friend fix_holder<self_type, N, Nth<N>> const& get(self_type const& self) { return self; }

    template<std::size_t N>
    friend fix_holder<self_type, N, Nth<N>>&& get(self_type&& self) { return std::move(self); }
};

} // ns

template<typename... Fs>
ns::fix_type<make_integer_sequence<int, sizeof...(Fs)>, Fs...> fix(Fs&&... fs)
{ return { std::forward<Fs>(fs)... }; }

namespace std {

template<std::size_t N, typename Seq, typename... Fs>
struct tuple_element<N, ns::fix_type<Seq, Fs...>> {
    using type = typename ns::fix_type<Seq, Fs...>::template Nth<N>;
};

} // std

#include <cassert>

int main()
{
    using std::get;

    /*
     * Example from http://en.wikipedia.org/wiki/Mutual_recursion:
     *
     *     bool is_even(unsigned int n)
     *         if (n == 0)
     *             return true;
     *         else
     *             return is_odd(n - 1);
     *
     *     bool is_odd(unsigned int n)
     *         if (n == 0)
     *             return false;
     *         else
     *             return is_even(n - 1);
     *
     */

    auto even_odd = fix(
            // even
            [](auto&& selves, int n) -> bool
            {
                auto& odd = get<1>(selves);
                return n == 0 || odd(n - 1);
            },
            // odd
            [](auto&& selves, int n) -> bool
            {
                auto& even = get<0>(selves);
                return n != 0 && even(n - 1);
            }
    );

    auto& even  = get<0>(even_odd);
    auto& odd   = get<1>(even_odd);

    assert( even(42) );
    assert( !even(43) );
    assert( !odd(42) );
    assert( odd(43) );
}