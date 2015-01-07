#include <iostream>

struct Foo
{
    int _m;
    Foo(int m): _m(m)
    {
    }
    Foo& operator=(const Foo& rhs) // remove the reference to see the difference
    {
        _m = rhs._m;
    	return *this;
    }
};

int main()
{
	Foo a(1), b(2), c(3);

	(a = b) = c;

	std::cout << a._m << " " << b._m << " " << c._m;
}