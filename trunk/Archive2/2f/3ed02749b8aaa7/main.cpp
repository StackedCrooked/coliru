#include <iostream>
#include <cstdlib>
#include <new>

struct A
{
    int a;
	A(){ std::cout << "Constructor\n"; a = 3; }
	void* operator new(std::size_t t) noexcept
	{
		::operator new(t);
        return NULL;
	}
};

int main()
{
    new A();
}