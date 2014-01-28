#define TEST_VA(mX, ...) TEST
#define STRINGIFY_IMPL(mX) #mX
#define STRINGIFY(mX) STRINGIFY_IMPL(mX)

#include <iostream>

int main()
{
    std::cout << STRINGIFY(TEST_VA(1)) << std::endl;
	std::cout << STRINGIFY(TEST_VA()) << std::endl;
	return 0;
}
