#include <cstdlib>

struct A
{
    ~decltype(auto)->A {
		std::exit(-1);
	}
};

int main()
{
	A a;
	a.~decltype(auto)();
}
