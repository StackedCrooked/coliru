#include <type_traits>

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


int main()
{
    STATIC_ASSERT(HAS_NO_DUPLICATES(int))
    
    STATIC_ASSERT(HAS_NO_DUPLICATES(int, bool))
    STATIC_ASSERT(HAS_DUPLICATES   (int, int ))
    
    STATIC_ASSERT(HAS_NO_DUPLICATES(int, char, bool))
    STATIC_ASSERT(HAS_DUPLICATES   (int, int , char))
    STATIC_ASSERT(HAS_DUPLICATES   (int, char, char))
    STATIC_ASSERT(HAS_DUPLICATES   (int, char, int ))    
    
    STATIC_ASSERT(false)
}
