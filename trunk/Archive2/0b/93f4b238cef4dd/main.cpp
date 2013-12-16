#include <iostream>

static void foo(long long *p)
{
    std::cout << *p << std::endl;
}
 
int main()
{
    static_assert(sizeof(long) == sizeof(long long), "long is shorter than long long");
	std::cout << "sizeof long = " << sizeof(long) << ", sizeof long long = " << sizeof(long long) << std::endl;
	long n = 42;
	foo(&n);
	return 0;
}
