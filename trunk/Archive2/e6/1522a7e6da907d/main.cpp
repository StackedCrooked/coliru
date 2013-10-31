#include <type_traits>

template< typename Type, std::size_t ExpectedSize, std::size_t ActualSize = 0 >
struct validate_size : std::true_type
{
    static_assert( ActualSize == ExpectedSize, "actual size does not match expected size" );
};

template< typename Type, std::size_t ExpectedSize >
struct validate_size< Type, ExpectedSize, 0 > : validate_size< Type, ExpectedSize, sizeof( Type ) > {};

int main()
{
    static_assert( validate_size< int, 4 >::value, "Oops" );
    static_assert( validate_size< int, 5 >::value, "Oops2" );
}
