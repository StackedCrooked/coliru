#include <type_traits>

template< typename T >
using cond = typename std::conditional_t< std::is_void< T >::value , std::true_type , std::false_type >::type;

static_assert( cond< void >() , "" );

int main() {}