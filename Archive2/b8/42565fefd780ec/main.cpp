#include <iostream>
#include <utility>
#include <limits>

using namespace std;

int main()
{
    //size_t x = std::numeric_limits<unsigned int>::max();
	unsigned int x = 0xffffffff;
    cout << "x " << hex << x << "\n";
    
	unsigned int y = 0xffffffff;
	//unsigned int y = 0x10;
    cout << "y " << hex << y << "\n";
    
	size_t res = (size_t)x * y;
	cout << "z " << hex << res << "\n";

	std::cout << "\njob done\n";
	return 0;
}