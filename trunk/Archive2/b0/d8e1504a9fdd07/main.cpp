template <typename...> struct tuple;
template <typename...> void slice();
template <int Index, typename...> using slice_result = decltype(slice<Index>);
template <typename Tuple, typename... Tuples, int... ElementIndices,
          typename =
              typename tuple<slice_result<ElementIndices, Tuples...>,
                             slice_result<ElementIndices, Tuples...>...>::type>
void zip_with(Tuple...);
decltype(zip_with(0))