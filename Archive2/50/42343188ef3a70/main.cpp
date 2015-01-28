#include <cstddef>
#include <type_traits>

using A = decltype( (char*)0 - (char*)0 );
static_assert( std::is_same<A, std::ptrdiff_t>{} );

int main()
{
}
