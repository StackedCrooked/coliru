#include "stdafx.h"

class A
{
public:
	A():
	p1(p2),
	p2(new int)
	{}

	void free()
	{
		delete p1;
	}
private:
	int* p1;
	int* p2;
};

A a1;

void func1()
{
	A a2;
	a2.free();
}

void func2()
{
	a1.free();
}

int _tmain(int argc, _TCHAR* argv[])
{
	func2();
	func1();
	return 0;
}