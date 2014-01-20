#include <cstring>
#include <iosfwd>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
#define DBG(x) { cout << setw(30) << left << #x << x << endl; }

#define NAME(prefix,suffix) prefix##suffix

#define MAKE_10(type,prefix)\
    type NAME(prefix,0); \
	type NAME(prefix,1); \
	type NAME(prefix,2); \
	type NAME(prefix,3); \
	type NAME(prefix,4); \
	type NAME(prefix,5); \
	type NAME(prefix,6); \
	type NAME(prefix,7); \
	type NAME(prefix,8); \
	type NAME(prefix,9);

#define MAKE_100(type, prefix)\
	MAKE_10(type,NAME(prefix,0))\
	MAKE_10(type,NAME(prefix,1))\
	MAKE_10(type,NAME(prefix,2))\
	MAKE_10(type,NAME(prefix,3))\
	MAKE_10(type,NAME(prefix,4))\
	MAKE_10(type,NAME(prefix,5))\
	MAKE_10(type,NAME(prefix,6))\
	MAKE_10(type,NAME(prefix,7))\
	MAKE_10(type,NAME(prefix,8))\
	MAKE_10(type,NAME(prefix,9))\

#define MAKE_1000(type,prefix)\
	MAKE_100(type,NAME(prefix,0))\
	MAKE_100(type,NAME(prefix,1))\
	MAKE_100(type,NAME(prefix,2))\
	MAKE_100(type,NAME(prefix,3))\
	MAKE_100(type,NAME(prefix,4))\
	MAKE_100(type,NAME(prefix,5))\
	MAKE_100(type,NAME(prefix,6))\
	MAKE_100(type,NAME(prefix,7))\
	MAKE_100(type,NAME(prefix,8))\
	MAKE_100(type,NAME(prefix,9))\

int main()
{
	MAKE_1000(int,a);

	a000 = 0;

	a666 = 666;

	std::cout << a000 << std::endl;
	std::cout << a666 << std::endl;
	std::cout << sizeof(a999) << std::endl;
}
