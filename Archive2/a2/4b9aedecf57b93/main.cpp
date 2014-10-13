namespace std {
typedef int size_t;
template <std::size_t, class> class tuple_element;
template <std::size_t, typename...> struct _Tuple_impl;
template <typename... _Elements> class tuple : _Tuple_impl<0, _Elements...> {};
template <typename Computation> using eval_t = typename Computation::type;
template <typename...> struct requires;
template <typename... Concepts>
using Requires = typename requires<Concepts...>::type;
template <int, typename Tuple>
using TupleElement = eval_t<tuple_element<0, Tuple> >;
namespace concepts {
template <typename> struct Tuple;
namespace detail {
template <typename... Tuples, Requires<concepts::Tuple<Tuples>...>...>
std::tuple<TupleElement<0, Tuples>...> slice;
template <typename... = decltype(detail::slice<>...)