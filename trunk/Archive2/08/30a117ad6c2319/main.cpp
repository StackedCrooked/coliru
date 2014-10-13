template <int, class> class tuple_element;
template <typename...> struct tuple;
template <typename... Tuples>
tuple<typename tuple_element<0, Tuples>::type...> slice(...);
template <int Index, typename...> using slice_result = decltype(slice<Index>);
template <typename Tuple, typename... Tuples, int... ElementIndices,
          typename tuple<slice_result<ElementIndices, Tuples...>,
                         slice_result<ElementIndices, Tuples...>...>::type...>
void zip_with(Tuple &&...);
template <typename... = decltype(zip_with(0 0 ...))