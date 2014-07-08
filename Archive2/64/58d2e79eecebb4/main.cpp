#include <iostream>


int main() {
    int value = 0x12345678;

    std::cout << "Last 1 byte: " << std::hex << (int)*(char*)&value << " in hex" << std::endl;
    std::cout << "Last 2 bytes: " << std::hex << *(short*)&value << " in hex" << std::endl;
	return 0;
}