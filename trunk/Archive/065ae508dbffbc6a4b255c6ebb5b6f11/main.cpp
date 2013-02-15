#include <tuple>
#include <type_traits>

template<typename T, typename /*disambiguator*/>
struct StrongTypedef
{
    StrongTypedef(const T & data = T()) : data_(data) {}    
    operator const T&() const { return data_; }        
    
    T data_;
};

#define STRONG_TYPEDEF(Type, Name) \
    typedef StrongTypedef<Type, struct Name##_> Name;

#define STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__);

#define IS_SAME(A, B) std::is_same<A, B>::value

#define TUPLE_ELEMENT(Index, Tuple) typename std::tuple_element<Index, Tuple>::type
    
    
template<typename El, typename Tuple, int Index>
struct _index_of
{
    STATIC_ASSERT(Index < std::tuple_size<Tuple>::value)
    static constexpr int value = IS_SAME(TUPLE_ELEMENT(Index, Tuple), El) ? Index : _index_of<El, Tuple, Index + 1>::value;
};


template<typename El, typename ...TupleTypes>
struct index_of;

template<typename El, typename ...TupleTypes>
struct index_of<El, std::tuple<TupleTypes...> >
{
    static constexpr int value = _index_of<El, std::tuple<TupleTypes...>, 0>::value;    
};

#define INDEX_OF(El, Tuple) \
    index_of<El, Tuple>::value


int main()
{

STRONG_TYPEDEF(int,  _)
STRONG_TYPEDEF(char, x)

STATIC_ASSERT(INDEX_OF(x, std::make_tuple(x)) == 0)

STATIC_ASSERT(INDEX_OF(x, std::make_tuple(x, _)) == 1)
STATIC_ASSERT(INDEX_OF(x, std::make_tuple(_, x)) == 1)

STATIC_ASSERT(INDEX_OF(x, std::make_tuple(x, _, _)) == 0)
STATIC_ASSERT(INDEX_OF(x, std::make_tuple(_, x, _)) == 1)
STATIC_ASSERT(INDEX_OF(x, std::make_tuple(_, _, x)) == 2)
}