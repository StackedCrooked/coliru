#include <experimental/optional>

int main()
{
    constexpr auto o = std::experimental::make_optional(5);
    static_assert( *o == 5, "it workses" );
}