#include <type_traits>
#include <iostream>

#include <cstdlib>

struct A
{
    
    template< typename type >
    void
    operator () (type const &&) const = delete;
    
    template< typename type >
    std::enable_if_t< std::is_same< std::remove_cv_t< std::remove_reference_t< type > >, double >::value >
    operator () (type &&) const
    {
        std::cout << "1" << std::endl;
        std::cout << __PRETTY_FUNCTION__ << std::endl << std::endl;
    }
    
    template< typename type >
    std::enable_if_t< !std::is_same< std::remove_cv_t< std::remove_reference_t< type > >, double >::value >
    operator () (type &&) const
    {
        std::cout << "2" << std::endl;
        std::cout << __PRETTY_FUNCTION__ << std::endl << std::endl;
    }
    
};

int main() 
{
    A const a{};
    { // desired
        double d{};
        a(std::move(d));
        int i{};
        a(std::move(i));
    }
    { // undesired (I want a hard error)
        double const d{};
        a(d);
        int const i{};
        a(i);
    }
    { // undesired (I want a hard error)
        double d{};
        a(d);
        int i{};
        a(i);
    }
    return EXIT_SUCCESS;
}
