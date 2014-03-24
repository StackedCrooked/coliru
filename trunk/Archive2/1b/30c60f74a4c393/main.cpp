#include <type_traits>

void f(unsigned int y) { }
template<typename T> void f(T const&) { static_assert(0, "STATIC CASTED!"); }

int main ()
{
	unsigned int y;
	f(y);
}
