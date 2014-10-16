#include <iostream>
#include <cstring>

int main()
{
    char *b = new char[10]{0};

	char *zeroes = new char[10];
	memset(zeroes, 0, 10);

	std::cout << memcmp(b, zeroes, 10); // 0 expected
}
