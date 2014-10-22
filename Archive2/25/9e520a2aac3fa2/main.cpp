#include <iostream>
#include <iomanip>

static float ident(float f)
{
    return f;
}

int main()
{
	std::cout << std::boolalpha << "15.8 == 15.8f: " << (15.8 == ident(15.8)) << std::endl;
	return 0;
}
