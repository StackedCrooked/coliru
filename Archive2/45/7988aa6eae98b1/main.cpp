#include <iostream>
 
struct A {
   double x;
};
const A* a = new A();
 
decltype( a->x ) x3;       // type of x3 is double (declared type)
decltype((a->x)) x4 = x3;  // type of x4 is const double& (lvalue expression)
 
template <class T, class U>
auto add(T t, U u) -> decltype(t + u); // return type depends on template parameters
 
int main() 
{
 int z = 0;
    auto i = 3;
	auto &r = i;
	const auto &cr = i;
	// auto i = 3, i2 = 4.5;
	i = 3;
	auto i2 = 4.5;

	decltype(i) j;
	decltype((i)) k(z);
}