#include <type_traits>

template <template<class...> class> using void_t = void;

template <typename, typename=void> struct has_foo : std::false_type {};

template <typename T>
struct has_foo<T, void_t<T::template foo>>  : std::true_type {};

struct Outer
{
    template <class, class, class> struct foo {};
};

int main()
{
    static_assert( has_foo<Outer>{}, "" );
}