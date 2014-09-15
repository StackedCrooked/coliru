#include <iostream>
#include <utility>
#include <type_traits>

template< template< typename ...formal > class base >
struct is_derived_from_impl
{
    
    template< typename ...actual >
    std::true_type
    operator () (base< actual... > *) const;
    
    std::false_type
    operator () (void *) const;
    
};

template< typename derived, template< typename ... > class base >
using is_derived_from = typename std::result_of< is_derived_from_impl< base >(typename std::remove_cv< derived >::type *) >::type;

template <typename... Ts>
struct B {};

template< typename D >
using is_derived_from_B = is_derived_from< D, B >;

template <typename... Ts>
struct D : B<Ts...> {};

template <typename... Ts>
struct D1 : D<Ts...> {};

template <typename... Ts>
struct Other {};

int main()
{
    std::cout << is_derived_from_B<D<int, int>>::value << std::endl;
    std::cout << is_derived_from_B<D1<int, int>>::value << std::endl;
    std::cout << is_derived_from_B<D<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_B<const D<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_B<Other<int, char, float>>::value << std::endl;
    std::cout << is_derived_from_B<int>::value << std::endl;
}
