#include <cmath>
#include <functional>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <set>
#include <utility>
#include <utility>
#include <vector>

#include <boost/type_traits.hpp>

using namespace std;
#define DBG(x) { cout << left << setw(45) << #x << boolalpha << (x) << endl; }

struct A {};

struct B : virtual A {};

struct C : virtual A {};

struct D : B,C {};

struct E : A{};

struct F : B,C { int a; };

int main()
{
    DBG((boost::is_virtual_base_of<A,A>::value));
	DBG((boost::is_virtual_base_of<A,B>::value));
	DBG((boost::is_virtual_base_of<A,C>::value));
	DBG((boost::is_virtual_base_of<A,D>::value));

	cout << endl;

	DBG((is_base_of<A,A>::value));
	DBG((is_base_of<A,B>::value));
	DBG((is_base_of<A,C>::value));
	DBG((is_base_of<A,D>::value));

	cout << endl;

	DBG((boost::is_virtual_base_of<E,A>::value));
	DBG((boost::is_virtual_base_of<E,E>::value));

	cout << endl;

	DBG((is_base_of<E,A>::value));
	DBG((is_base_of<E,E>::value));

	cout << endl;

	DBG((boost::is_virtual_base_of<F,A>::value));
	DBG((boost::is_virtual_base_of<F,B>::value));
	DBG((boost::is_virtual_base_of<F,C>::value));
	DBG((boost::is_virtual_base_of<F,D>::value));

	cout << endl;

	DBG((is_base_of<F,A>::value));
	DBG((is_base_of<F,B>::value));
	DBG((is_base_of<F,C>::value));
	DBG((is_base_of<F,D>::value));

}

