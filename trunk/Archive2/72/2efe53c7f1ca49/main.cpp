#include <iostream>
 
int main() {
    std::cout << "Printed together: '";
    std::cout << (char)0xC3;
	std::cout << (char)0xA2;
    std::cout << "'\n";
    
    // uncomment the following lines to see what they print. Coliru doesn't allow sharing the output due to the fact that it causes an encoding error. 
    //std::cout << "Printed separated: '";
    //std::cout << (char)0xC3;
    //std::cout << '/';
    //std::cout << (char)0xA2;
    //std::cout << "'\n";
}
