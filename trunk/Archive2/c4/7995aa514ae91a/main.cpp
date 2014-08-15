template<typename Tuple>
using RuntimeTupleElement = meta::BindOver<variant, tuples::ToList<Tuple>>;

namespace variant_detail {

template<typename Tuple, typename Int>
RuntimeTupleElement<Tuple> runtime_get(Tuple&&, Int, indices<>)
{ std::abort(); }

template<typename Tuple, typename Int, int Index, int... Indices>
RuntimeTupleElement<Tuple> runtime_get(Tuple&& tuple, Int i, indices<Index, Indices...>)
{
    if(i == Index) {
        return annex::emplace<Index>(adl::get<Index>(std::forward<Tuple>(tuple)));
    } else {
        return runtime_get(std::forward<Tuple>(tuple), i, indices<Indices...>());
    }
}

} // variant_detail

template<typename Tuple, typename Int>
RuntimeTupleElement<Tuple> runtime_get(Tuple&& tuple, Int i)
{ return variant_detail::runtime_get(std::forward<Tuple>(tuple), i, indices_for<Tuple>()); }