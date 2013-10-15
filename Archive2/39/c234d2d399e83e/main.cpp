#include <iostream>
#include <type_traits>
#include <string>

#include <cstdlib>

template<class T>
using invoke = typename T::type;

template< typename T >
class A
{

    struct B {};

public :

    struct U : B {};

    template< typename D, typename R = void >
    using enable_if_is_B = std::enable_if< std::is_base_of< B, D >::value, R >;

    template< typename D, typename R = void >
    using enable_if_is_not_B = std::enable_if< !std::is_base_of< B, D >::value, R >;

    template< typename D >
    auto
    operator () (D const &) const
    -> invoke< enable_if_is_B< D > >
    {
        std::cout << "D is B" << std::endl;
    }

    template< typename D >
    auto
    operator () (D const &) const
    -> invoke< enable_if_is_not_B< D > >
    {
        std::cout << "D is not B" << std::endl;
    }

};

template< typename T >
struct B
{

    using A_type = A< T >;

    template< typename D, typename R = void >
    using enable_if_is_B = typename A_type::template enable_if_is_B< D, R >;

    template< typename D, typename R = void >
    using enable_if_is_not_B = typename A_type::template enable_if_is_not_B< D, R >;

    template< typename D >
    auto
    operator () (D const &) const
    -> invoke< enable_if_is_B< D > >
    {
        std::cout << "D is B!" << std::endl;
    }

    template< typename D >
    auto
    operator () (D const &) const
    -> invoke< enable_if_is_not_B< D > >
    {
        std::cout << "D is not B!" << std::endl;
    }

};

int main()
{
    using T = struct Z;
    using A_type = A< T >;
    using U = typename A_type::U;
#if 0
    using X = A< T >;
#else
    using X = B< T >;
#endif
    X const x{};
    x(0);
    x(U());
    return EXIT_SUCCESS;
}