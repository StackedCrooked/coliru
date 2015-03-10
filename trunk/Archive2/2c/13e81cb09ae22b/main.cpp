#include <iostream>
 
int main() {
    std::cout << "Printed together: '";
    std::cout << (char)0xC3;
	std::cout << (char)0xA2;
    std::cout << "'\n";
    std::cout << "Printed separated: '";
    std::cout << (char)0xC3;
    std::cout << '/';
    std::cout << (char)0xA2;
    std::cout << "'\n";
}
