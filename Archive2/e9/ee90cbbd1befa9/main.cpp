#include <type_traits>

int main()
{
    using F = void();
    static_assert( std::is_same<F, F const>(), "" );
    static_assert( std::is_same<F&, F const&>(), "" );
}