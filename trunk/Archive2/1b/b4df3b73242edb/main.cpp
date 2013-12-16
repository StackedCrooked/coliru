#include <iostream>
#include <fstream>
#include <iterator>

int main() {
    std::string ciphero;
std::ifstream infilo;
 infilo.open("main.cpp");
 infilo.seekg(0, std::ios::end);   
 ciphero.reserve(infilo.tellg());
 infilo.seekg(0, std::ios::beg);
 ciphero.assign((std::istreambuf_iterator<char>(infilo)),
 std::istreambuf_iterator<char>());
 std::cout << ciphero;
 
 return 0;
}