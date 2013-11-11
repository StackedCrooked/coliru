#include <iostream>
#include <boost/array.hpp>

struct T
{
    T(int x)
		: ar({x}), len(1)
	{};
    
    T(int x, int y, int z)
    	: ar({x,y,z}), len(3)
	{};
	
	boost::array<int, 4> ar;
	size_t len;
};

int main() {
	T a(42);
    std::cout << a.ar[0] << ',' << a.ar[1] << ':' << a.len << '\n';
    
    T b(1, 2, 3);
    std::cout << b.ar[0] << ',' << b.ar[1] << ',' << b.ar[2] << ',' << b.ar[3] << ':' << b.len << '\n';
}