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
    apply_helper(std::conditional_t<
        std::is_convertible<Args, Value>::value, null, Args>...
    );
    
    template <typename...>
    static std::true_type apply_helper(...);
    
    template <typename... Args>
    static auto apply(Args&&...)
    -> decltype(apply_helper<
        std::remove_reference_t<Args>...>(std::declval<Args>()...));
public:
    template <typename Tuple>
    using value = decltype(
        apply(
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

int main()
{
    static_assert(has_type<bool, std::tuple<bool, char, int>>{}, "");
}