#include <type_traits>

template <template<class> class> using void_templ = void;

template <typename, typename=void> struct has_foo : std::false_type {};

template <typename T>
struct has_foo<T, void_templ<T::template foo>>  : std::true_type {};

struct Outer
{
    template <class> struct foo {};
};

int main()
{
    static_assert( has_foo<Outer>{}, "" );
    static_assert( !has_foo<std::true_type>{}, "" );
}