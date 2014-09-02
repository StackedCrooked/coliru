template<int... Indices>
struct indices
{
    using next = indices<Indices..., sizeof...(Indices)>;
};

template<int n>
struct build_indices
{
    using type = typename build_indices<n - 1>::type::next;
};

template<>
struct build_indices<0>
{
    using type = indices<>;
};

template<int n>
using build_indices_t = typename build_indices<n>::type;

template<typename T, typename U>
struct concat;

template<int... Is, int... Us>
struct concat<indices<Is...>, indices<Us...>>
{
    using type = indices<Is..., Us...>;
};

template<typename T, typename U>
using concat_t = typename concat<T, U>::type;

template<int first, int last, typename T>
struct index_from_range_impl;

template<int first, int last, int... Is>
struct index_from_range_impl<first, last, indices<Is...>>
{
    using type = indices<(Is + first)...>;
};

template<int first, int last>
struct index_from_range
{
    using type = typename index_from_range_impl<first, last, build_indices_t<(last + 1) - first>>::type;
};

template<int first, int last>
using index_from_range_t = typename index_from_range<first, last>::type;

template<int i, int j>
struct Range;

template<typename Range, typename Sequence>
struct find_args_not_in_pack;

template<int I, int U, int... Is, int... Us>
struct find_args_not_in_pack<indices<I, Is...>, indices<U, Us...>>
{
    using type = concat_t<indices<U>, typename find_args_not_in_pack<indices<Is...>, indices<Us...>>::type>;
};

template<int J, int... Is, int... Us>
struct find_args_not_in_pack<indices<J, Is...>, indices<J, Us...>>
{
    using type = indices<>;
};

template<typename Seq1, typename Seq2>
using find_arg_not_in_pack_t = typename find_args_not_in_pack<Seq1, Seq2>::type;

int main()
{
    
}