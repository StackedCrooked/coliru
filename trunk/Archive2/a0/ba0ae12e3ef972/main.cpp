#include <iostream>
#include <cstdlib>
#include <cassert>
 
template <typename A, typename B>
void ASSERT_EQ(A const a, B const b)
{
    if(a != b)
    {
        std::cout << "assertion failed: " << a << " != " << b << "\n"; \
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