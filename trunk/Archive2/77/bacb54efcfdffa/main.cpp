#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

int main() {
    //std::ifstream file("output.txt");    
    std::istream_iterator<std::string> first(std::cin), last;
    std::cout << std::count(first, last, "line");
}