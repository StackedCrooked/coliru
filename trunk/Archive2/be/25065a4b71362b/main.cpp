#include <iostream>

using std::cout;
using std::endl;

struct S
{
    long l;
};

struct V
{
    long d;
};

struct A
{
    long a;
};

struct B : A, S, V
{ 
    void * operator new(std::size_t t)
	{
		cout << t << endl;
		return ::operator new(t);
	}
};

B *b = new B;

int main()
{
	b -> a = 23;
	b -> l = 3L;
	b -> d = 52L;
}