#include <tuple>

template<bool B> struct bool_type {
    static constexpr bool value = B;
};
using true_type  = bool_type<true>;
using false_type = bool_type<false>;

template<typename T> struct voidify { using type = void; };
template<typename T> using voidify_t = typename voidify<T>::type;

template<typename T, typename = void>
struct query: false_type {};
template<typename T>
struct query<T, voidify_t<typename std::tuple_size<T>::type>>
: true_type {};

int main()
{
    static_assert( query<std::tuple<>>::value, "" );
    static_assert( !query<int>::value, "" );
    
    // error: incomplete type 'std::tuple_size<void()>' used in nested name specifier
    static_assert( !query<void()>::value, "" );
}