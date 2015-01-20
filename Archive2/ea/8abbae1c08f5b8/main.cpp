#include <type_traits>

template <template<class...> class> struct  void_t {using type = void;};

template <typename, typename=void> struct has_foo : std::false_type {};

template <typename T>
struct has_foo<T, typename void_t<T::template foo>::type>  : std::true_type {};

struct Outer
{
   // template <class, class, class> struct foo {};
};

int main()
{
    static_assert( has_foo<Outer>{}, "" );
}