#include <iostream>
#include <string>
#include <vector>

int main() {
    uint8_t data[42];
    for(auto i = std::begin(data); i != std::end(data); i++){
		std::cout << static_cast<unsigned char>(i);
	}
	std::cout <<std::endl;
}
