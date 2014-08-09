template<typename T> struct tuple_size;
template<typename T> struct tuple_size<T const>: tuple_size<T> {};

template<bool B> struct bool_type {
    static constexpr bool value = B;
};
using true_type  = bool_type<true>;
using false_type = bool_type<false>;

template<typename T, typename = void>
struct query: false_type {};
template<typename T>
struct query<T, typename tuple_size<T>::type>
: true_type {};

int main()
{
    // error: invalid use of incomplete type 'struct tuple_size<void()>
    static_assert( !query<void()>::value, "" );
}