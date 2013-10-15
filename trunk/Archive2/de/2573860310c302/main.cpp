#include <iostream>
#include <type_traits>
#include <string>

#include <cstdlib>

template< typename T >
class A
{

    struct B {};

public :

    struct U : B {};

    template< typename D, typename R = void >
    using enable_if_is_B = typename std::enable_if< std::is_base_of< B, D >::value, R >::type;

    template< typename D, typename R = void >
    using enable_if_is_not_B = typename std::enable_if< !std::is_base_of< B, D >::value, R >::type;

    template< typename D >
    auto
    operator () (D const &) const
    -> enable_if_is_B< D >
    {
        std::cout << "D is B" << std::endl;
    }

    template< typename D >
    auto
    operator () (D const &) const
    -> enable_if_is_not_B< D >
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
    -> enable_if_is_B< D >
    {
        std::cout << "D is B!" << std::endl;
    }

    template< typename D >
    auto
    operator () (D const &) const
    -> enable_if_is_not_B< D >
    {
        std::cout << "D is not B!" << std::endl;
    }

};

int main()
{
    using T = struct Z;
    using A_type = A< T >;
    using U = typename A_type::U;

    using X = B< T >;
    X const x = X();
    x(0);
    x(U());
    return EXIT_SUCCESS;
}