#include <iostream>
#include <tuple>
#include <type_traits>
#include <stdint.h>

    
template<typename T, typename /*disambiguator*/>
struct StrongTypedef
{
    StrongTypedef(const T & data = T()) : data_(data) {}    
    operator const T&() const { return data_; }        
    
    T data_;
};

template<typename T, typename D>
std::ostream& operator<<(std::ostream& os, const StrongTypedef<T, D> & obj)
{
    return os << static_cast<const T&>(obj);
}

#define STRONG_TYPEDEF(Type, Name) \
    typedef StrongTypedef<Type, struct Name##_> Name;

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


#define STATIC_ASSERT(...) \
    static_assert(__VA_ARGS__, #__VA_ARGS__);

#define HAS_DUPLICATES(...) \
    has_duplicates< __VA_ARGS__ >::value

#define HAS_NO_DUPLICATES(...) \
    !HAS_DUPLICATES( __VA_ARGS__ )
    
    
#define TUPLE_ELEMENT(Index, Tuple) \
    typename std::tuple_element<Index, Tuple>::type    
    
#define IS_SAME(A, B) \
    std::is_same<A, B>::value

    
template<typename El, typename Tuple, int Index>
struct _index_of
{
    STATIC_ASSERT(Index < std::tuple_size<Tuple>::value)
    static constexpr int value = IS_SAME(TUPLE_ELEMENT(Index, Tuple), El) ? Index : _index_of<El, Tuple, Index + 1>::value;
};


template<typename El, typename ...TupleTypes>
struct index_of
{
    static constexpr int value = _index_of<El, std::tuple<TupleTypes...>, 0>::value;    
};

#define INDEX_OF(El, Tuple) \
    index_of<El, Tuple>::value

namespace Test {

STRONG_TYPEDEF(int,  _)
STRONG_TYPEDEF(char, x)

STATIC_ASSERT(INDEX_OF(x, std::make_tuple(x)) == 0)

STATIC_ASSERT(INDEX_OF(x, std::make_tuple(x, _)) == 1)
STATIC_ASSERT(INDEX_OF(x, std::make_tuple(_, x)) == 1)

STATIC_ASSERT(INDEX_OF(x, std::make_tuple(x, _, _)) == 0)
STATIC_ASSERT(INDEX_OF(x, std::make_tuple(_, x, _)) == 1)
STATIC_ASSERT(INDEX_OF(x, std::make_tuple(_, _, x)) == 2)

}
    

template<typename T, typename Tuple>
T& get(const Tuple & tuple)
{
    return std::get<index_of<T, Tuple>::value>(tuple);
}


// A "record" is a tuple where are elements are of different type.
// This enables access by type instead of index.
template<typename ...Args>
auto make_record(Args && ...args) -> std::tuple<Args...>
{
    STATIC_ASSERT(HAS_NO_DUPLICATES(Args...))
    return std::make_tuple(std::forward<Args>(args)...);
}
    
    
    

STRONG_TYPEDEF(uint64_t   , Id)
STRONG_TYPEDEF(std::string, Title)
STRONG_TYPEDEF(std::string, Author)
STRONG_TYPEDEF(std::string, Description)

int main()
{
    auto book = make_record(Id(120),
                            Title("Exploring the boundaries of the universe, a biography."),
                            Author("Your mom"));
                            
    auto title = get<Title>(book);
    auto author = get<Author>(book);
    
    std::cout << title << " was written by " << author << "." << std::endl;        
}
