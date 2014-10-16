#include <iostream>
#include <cstring>

int main()
{
    char const *a = "my string";
    char *b = new char[strlen(a) + 1]{0};

	char *zeroes = new char[strlen(a) + 1];
	memset(zeroes, 0, strlen(a) + 1);

	std::cout << memcmp(b, zeroes, strlen(a) + 1); // 0 expected
}
