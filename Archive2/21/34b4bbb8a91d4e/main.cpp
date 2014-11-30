#include <iostream>

int main()
{
    alignas(4096) char arr[564];
	std::cout << &arr;
}
