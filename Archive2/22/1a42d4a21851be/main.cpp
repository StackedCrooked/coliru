#include <type_traits>

int main()
{
    struct A {};
	struct B {};
	A hallo(B());
	static_assert( std::is_same<decltype(hallo), A(B(*)())>::value );
}
