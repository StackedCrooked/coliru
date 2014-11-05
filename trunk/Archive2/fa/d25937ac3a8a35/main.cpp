#include <type_traits>

const int i = 0xffffffff;

static_assert( std::is_same<decltype( 0xffffffff ), unsigned int>(), "" );

int main()
{
}