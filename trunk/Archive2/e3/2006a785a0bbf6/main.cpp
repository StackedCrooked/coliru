#include <iostream>


int main() {
    int value = 0x12345678;
    void * p = &value;

    std::cout << "Last 1 byte: " << std::hex << (int)*(char*)p << " in hex" << std::endl;
    std::cout << "Last 2 bytes: " << std::hex << *(short*)p << " in hex" << std::endl;
	return 0;
}