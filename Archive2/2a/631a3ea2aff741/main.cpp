#include <iostream>
#include <cstdlib>
#include <cassert>
 
#define ASSERT_EQ(a, b) \
{ \
   assert_eq_impl((a), (b), __LINE__, __FILE__); \
}
template <typename A, typename B>
void assert_eq_impl(A const a, B const b, int const line, char const * const file)
{
    if(a != b)
    {
        std::cout << "assertion failed: (" << file << "):" << line << " " << a << " != " << b << "\n"; \
        std::abort();
    }
}
 
int main() {
    int x = 42;
	unsigned long long y = 123;
    assert(x == 42); // ok
    assert(y == 123); // ok
	ASSERT_EQ(x, 42); // ok
	ASSERT_EQ(y, 123); // fails on -Werror
}