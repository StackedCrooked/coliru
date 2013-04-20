#include <iostream>
#include <sstream>
#include <vector>


int main () {
    std::stringstream script;
    script << "load('SCANNER', 24);" 
		   << "load('TANK', 24);" 
		   << "load('ARTILLRY', 12);";

	std::vector<char> buffer(4096);
	std::cout << script.readsome(&buffer[0], buffer.size()) << std::endl;
    std::cout << script.readsome(&buffer[0], buffer.size()) << std::endl;
    std::cout << script.readsome(&buffer[0], buffer.size()) << std::endl;
}
