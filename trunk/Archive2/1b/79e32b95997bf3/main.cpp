#include <iostream>


int main() {
    int value = 0x12345678;

    std::cout << "Last 1 byte: " << (int)*(char*)&value << " in base 10" << std::endl;
    std::cout << "Last 2 bytes: " << *(short*)&value << " in base 10" << std::endl;
	return 0;
}