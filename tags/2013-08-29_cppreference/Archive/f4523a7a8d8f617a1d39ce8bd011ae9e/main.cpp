#include <iostream>
#include <tuple>
#include <type_traits>


#define STATIC_ASSERT(...) \
    static_assert(__VA_ARGS__, #__VA_ARGS__);


template<typename T, typename /*disambiguator*/>
struct StrongTypedef
{
    StrongTypedef(const T & data = T()) : data_(data) {}
    operator const T&() const { return data_; }

    T data_;
};


#define STRONG_TYPEDEF(Type, Name) \
    typedef StrongTypedef<Type, struct Name##_> Name;


#define IS_SAME(A, B) \
    std::is_same<A, B>::value


#define TUPLE_ELEMENT(Index, Tuple) \
    typename std::tuple_element<Index, Tuple>::type


namespace detail {


template<typename El, typename Tuple, int Index>
struct _index_of
{
    STATIC_ASSERT(Index < std::tuple_size<Tuple>::value)
    static constexpr int value = IS_SAME(TUPLE_ELEMENT(Index, Tuple), El) ? Index : _index_of<El, Tuple, Index + 1>::value;
};


} // namespace detail


template<typename El, typename ...TupleTypes>
struct index_of;


template<typename El, typename ...TupleTypes>
struct index_of<El, std::tuple<TupleTypes...> >
{
    static constexpr int value = detail::_index_of<El, std::tuple<TupleTypes...>, 0>::value;
};


#define INDEX_OF(El, Tuple) \
    index_of<El, Tuple>::value


template<typename T, typename ...Args>
struct is_any_of;


template<typename T, typename Arg>
struct is_any_of<T, Arg>
{
    static constexpr bool value = std::is_same<T, Arg>::value;
};


template<typename T, typename Head, typename ...Tail>
struct is_any_of<T, Head, Tail...>
{
    static constexpr bool value = std::is_same<T, Head>::value || is_any_of<T, Tail...>::value;
};


#define IS_ANY_OF(...) \
    is_any_of< __VA_ARGS__ >::value


template<typename Head, typename ...Tail>
struct has_duplicates;


template<typename Head>
struct has_duplicates<Head> {  static constexpr bool value = false; };


template<typename Head, typename Tail>
struct has_duplicates<Head, Tail> {  static constexpr bool value = std::is_same<Head, Tail>::value; };


template<typename Head, typename Next, typename ...Tail>
struct has_duplicates<Head, Next, Tail...>
{
    static constexpr bool value =
        std::is_same<Head, Next>::value ||
        is_any_of<Head, Tail...>::value ||
        is_any_of<Next, Tail...>::value;
};


#define HAS_DUPLICATES(...) \
    has_duplicates< __VA_ARGS__ >::value


#define HAS_NO_DUPLICATES(...) \
    !HAS_DUPLICATES( __VA_ARGS__ )


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

    STATIC_ASSERT(HAS_NO_DUPLICATES(int))

    STATIC_ASSERT(HAS_NO_DUPLICATES(int, bool))
    STATIC_ASSERT(HAS_DUPLICATES   (int, int ))

    STATIC_ASSERT(HAS_NO_DUPLICATES(int, char, bool))
    STATIC_ASSERT(HAS_DUPLICATES   (int, int , char))
    STATIC_ASSERT(HAS_DUPLICATES   (int, char, char))
    STATIC_ASSERT(HAS_DUPLICATES   (int, char, int ))

    std::cout << "End of program." << std::endl;
}
