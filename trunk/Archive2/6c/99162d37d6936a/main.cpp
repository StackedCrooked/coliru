#include <utility>      // std::forward, std::integer_sequence
#include <type_traits>  // std::remove_reference_t
#include <tuple>        // tuple protocol, e.g. std::get, std::tuple_size

// substitute missing bits
namespace ersatz {

using std::size_t;

template<typename T> using remove_reference_t = typename std::remove_reference<T>::type;

template<typename Int, Int... Values>
struct integer_sequence {
    using value_type = Int;
    static constexpr size_t size() noexcept { return sizeof...(Values); }
};

template<size_t... Values> using index_sequence = integer_sequence<size_t, Values...>;

namespace detail {
    
template<size_t N, typename Int, Int... Ns>
struct build_sequence: build_sequence<N - 1, Int, N - 1, Ns...> {};

template<typename Int, Int... Ns>
struct build_sequence<0, Int, Ns...> {
    using type = integer_sequence<Int, Ns...>;
};
    
} // detail

template<typename T, T N> using make_integer_sequence = typename detail::build_sequence<N, T>::type;
template<size_t N> using make_index_sequence = make_integer_sequence<size_t, N>;
template<typename... T> using index_sequence_for = make_index_sequence<sizeof...(T)>;

} // ersatz

using ersatz::integer_sequence;
using ersatz::make_index_sequence;
using ersatz::remove_reference_t;

namespace detail {

template<typename Functor, typename Zero, typename Tuple, typename Int>
Zero foldl(Functor&&, Zero&& zero, Tuple&&, integer_sequence<Int>)
{ return std::forward<Zero>(zero); }

template<typename Functor, typename Zero, typename Tuple, typename Int, Int Index, Int... Indices>
decltype(auto) foldl(Functor&& functor, Zero&& zero, Tuple&& tuple, integer_sequence<Int, Index, Indices...>)
{ return detail::foldl(
        functor
        , functor(std::forward<Zero>(zero), std::get<Index>(std::forward<Tuple>(tuple)))
        , std::forward<Tuple>(tuple)
        , integer_sequence<Int, Indices...> {}); }

} // detail

template<typename Functor, typename Zero, typename Tuple>
decltype(auto) foldl(Functor&& functor, Zero&& zero, Tuple&& tuple)
{
    return detail::foldl(
            std::forward<Functor>(functor)
            , std::forward<Zero>(zero)
            , std::forward<Tuple>(tuple)
            , make_index_sequence<std::tuple_size<remove_reference_t<Tuple>>::value>()
            );
}

/******** Demo ********/

#include <cassert>

namespace functors {

struct reverse_compose {
    template<typename Lhs, typename Rhs>
    auto operator()(Lhs&& lhs, Rhs&& rhs) const
    {
        return [lhs = std::forward<Lhs>(lhs), rhs = std::forward<Rhs>(rhs)](auto&&... args) mutable -> decltype(auto)
        { return rhs(lhs(std::forward<decltype(args)>(args)...)); };
    }
};

struct identity {
    template<typename T>
    T operator()(T&& t) const
    { return std::forward<T>(t); }
};

} // functors

int main()
{
    auto pipe = [](auto&&... fs) {
        return foldl(functors::reverse_compose {}, functors::identity {}, std::forward_as_tuple(std::forward<decltype(fs)>(fs)...));
    };
    auto f = pipe([](int i) { return 2 * i; }, [](long l) { return 1 - l; });
    auto r = f(5);
    static_assert( std::is_same<decltype(r), long>(), "Unexpected return type" );
    assert( r == -9l );
}