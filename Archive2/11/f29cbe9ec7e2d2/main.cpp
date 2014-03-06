#include <bitset>
#include <iostream>
#include <vector>

template <typename T>
void printBits(const T& t)
{
    std::bitset<sizeof(T)*8> bits(t);
	std::cout << bits << std::endl;
}

int main(int argc, char* argv[])
{
	unsigned char c = 10;
	int i = 20;
	float f = 32.3;

	std::cout << "char bits: "; printBits(c);
	std::cout << "int bits: "; printBits(i);
	std::cout << "float bits: "; printBits(f);

	std::cin.get();
	return 0;
}