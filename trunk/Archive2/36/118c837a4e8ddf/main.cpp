#include <iostream>

struct Foo
{
    Foo operator=(const Foo& f)
    {
        return *this;
    }
};

int main()
{
	Foo a, b, c;

	a = b = c;
}