#include <type_traits>
#include <tuple>

template <std::size_t... Indices>
struct index_sequence {
    typedef index_sequence<Indices..., sizeof...(Indices)> next;
};

template <std::size_t Start>
struct make_index_sequence {
    typedef typename make_index_sequence<Start - 1>::type::next type;
};

template <>
struct make_index_sequence<0> {
    typedef index_sequence<> type;
};

template <int n>
using make_index_sequence_t = typename make_index_sequence<n>::type;

template <typename Value, typename Sequence>
struct lookup;

template <typename Value, std::size_t... index>
struct lookup<Value, index_sequence<index...>>
{
private:
    struct null;
    
    template <typename... Args>
    static std::false_type
    apply(std::conditional_t<std::is_convertible<Args, Value>::value, null, Args>...);
    
    template <typename...>
    static std::true_type apply(...);
    
    template <typename... Args>
    static auto apply_helper(Args&&...)
    -> decltype(apply<std::remove_reference_t<Args>...>(std::declval<Args>()...));
public:
    template <typename Tuple>
    using value = decltype(
        apply_helper(
            std::declval<
                typename std::tuple_element<index, Tuple>::type
            >()...
        )
    );
};

template <typename Value, typename Tuple>
using has_type = decltype(
    typename lookup<Value,
                    make_index_sequence_t<std::tuple_size<Tuple>::value>
    >::template value<Tuple>{}
);

// Test:

struct A { };
struct B { };
struct C { };

typedef std::tuple<A, B, C> t1;
typedef std::tuple<C, A, A> t2;

// This will NOT fire:
static_assert(has_type<C, t1>{}, "");
// This WILL fire!:
// static_assert(has_type<B, t2>{}, "");

int main()
{
}