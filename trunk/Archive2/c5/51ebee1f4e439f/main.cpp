#include <iostream>
using namespace std;

struct Moveable
{
	Moveable(Moveable&&)
	{
		cout << "move" << endl;
	}

	Moveable()
	{
		cout << "ctor" << endl;
	}

	Moveable(const Moveable&)
	{
		cout << "copy" << endl;
	}

	void go()
	{

	}
};

struct MyClass
{
	MyClass(Moveable m)
		: m_m(move(m))
	{
		cout << "MyClass::Ctor" << endl;
	}

	MyClass(MyClass&& other)
		: m_m(move(other.m_m))

	{
		cout << "MyClass::move" << endl;
	}

	Moveable m_m;
};

Moveable calc()
{
	Moveable m;
	m.go();
	return m;
}

int main()
{
    auto c = calc();
}