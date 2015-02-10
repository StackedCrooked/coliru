#include <utility>
#include <type_traits>
#include <tuple>

template<typename...Ts> struct List;

template<typename T> struct ListFromTupleImpl;
template<typename...Ts> struct ListFromTupleImpl<std::tuple<Ts...>> { using type = List<Ts...>; };

template<typename T> using ListFromTuple = typename ListFromTupleImpl<T>::type;

template<typename...Ts> using TupleCat = decltype(std::tuple_cat(std::declval<Ts>()...));
template<typename...Ts> using ListFromTupleCat = ListFromTuple<TupleCat<Ts...>>;

template<unsigned P,typename T,typename I> struct RemoveFromListImpl;
template<unsigned P,typename...Ts,std::size_t...Is> struct RemoveFromListImpl<P,List<Ts...>,std::index_sequence<Is...>>
{
    using type = ListFromTupleCat<std::conditional_t<(Is==P),std::tuple<>,std::tuple<Ts>>...>;
};

// All elements < P
template<unsigned P,typename T,typename I> struct HeadImpl;
template<unsigned P,typename...Ts,std::size_t...Is> struct HeadImpl<P,List<Ts...>,std::index_sequence<Is...>>
{
    using type = TupleCat<std::conditional_t<(Is>=P),std::tuple<>,std::tuple<Ts>>...>;
};

// All elements >= P
template<unsigned P,typename T,typename I> struct TailImpl;
template<unsigned P,typename...Ts,std::size_t...Is> struct TailImpl<P,List<Ts...>,std::index_sequence<Is...>>
{
    using type = TupleCat<std::conditional_t<(Is<P),std::tuple<>,std::tuple<Ts>>...>;
};

template<typename N,unsigned P,typename T,typename I> struct InsertIntoListImpl
{
    using head = typename HeadImpl<P,T,I>::type;
    using tail = typename TailImpl<P,T,I>::type;
    using type = ListFromTupleCat<head,std::tuple<N>,tail>;
};

template<typename...Ts> struct List {
    /* ... */
    template<std::size_t P>
    using Remove = typename RemoveFromListImpl<P,List<Ts...>,std::index_sequence_for<Ts...>>::type;

    template<typename N,std::size_t P>
    using Insert = typename InsertIntoListImpl<N,P,List<Ts...>,std::index_sequence_for<Ts...>>::type;
};


static_assert(std::is_same
<
    List<int, char, float>::Remove<0>,
    List<char, float>
>(), "");

static_assert(std::is_same
<
    List<int, char, float>::Remove<1>,
    List<int, float>
>(), "");

static_assert(std::is_same
<
    List<int, char, float>::Insert<int, 0>,
    List<int, int, char, float>
>(), "");

static_assert(std::is_same
<
    List<int, char, float>::Insert<int, 2>,
    List<int, char, int, float>
>(), "");

int main(){}
