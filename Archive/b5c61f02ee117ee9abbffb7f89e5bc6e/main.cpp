#include <type_traits>

// Utility
template<typename...>
struct void_ { using type = void; };
template<typename... T>
using Void = typename void_<T...>::type;

template<typename T>
struct insane {
    using type = decltype(++std::declval<T&>());
};

template<typename T, typename Sfinae = void>
struct sane {};

template<typename T>
struct sane<T, Void<decltype(++std::declval<T&>())>> {
    using type = decltype(++std::declval<T&>());
};

int main()
{
    static_assert( std::is_same<insane<int>::type, int&>::value, "" );
    
    // Nothing bad happens!
    sane<void> {};
    
    // Ohnoez!
    insane<void> {};
}