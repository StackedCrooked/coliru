#include <type_traits>

auto& t()
{
    static const int i = 0;
	return i;
}

static_assert( std::is_same<decltype(t()), int const&>::value );

int main() {}