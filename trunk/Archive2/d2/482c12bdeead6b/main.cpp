#include <iostream>
#include <cstdlib>
#include <cassert>
 
#define ASSERT_EQ(a, b) do { \
    const auto & _a = (a); \
    const auto & _b = (b); \
    if (_a != _b) { \
        std::cout << "assertion failed: " << a << " != " << b << "\n"; \
    	std::abort(); \
    } \
} while(0)
 
int main() {
	int x = 42;
	unsigned long long y = 123;
    assert(x == 42); // ok
    assert(y == 123); // ok
	ASSERT_EQ(x, 42); // ok
	ASSERT_EQ(y, 123); // fails on -Werror
}