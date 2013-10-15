#include <iostream>
#include <typeinfo>
using namespace std;

int const * const foo()
{
    return nullptr;
}

int main()
{
	int x = 7;

	auto a1 = &x;
	cout << typeid(a1).name() << endl;

	auto a2 = const_cast<int const *>(&x);
	cout << typeid(a2).name() << endl;

	auto a3 = const_cast<int * const>(&x);
	cout << typeid(a3).name() << endl;

	auto a4 = const_cast<int const * const>(&x);
	cout << typeid(a4).name() << endl;

	auto a5 = const_cast<int const * const>(a4);
	cout << typeid(a5).name() << endl;

	auto a6 = (int const * const) &x;
	cout << typeid(a6).name() << endl;

	auto a7 = static_cast<int const * const>(a4);
	cout << typeid(a7).name() << endl;

	auto a8 = reinterpret_cast<int const * const>(a4);
	cout << typeid(a8).name() << endl;

	auto a9 = foo();
	cout << typeid(a9).name() << endl;

	int const * const a10 = &x;
	cout << typeid(a10).name() << endl;
	cout << ( typeid(a10) == typeid(a4) ) << endl;

	auto a12 = a10;
	cout << typeid(a12).name() << endl;
	cout << ( typeid(a12) == typeid(a4) ) << endl;
};
