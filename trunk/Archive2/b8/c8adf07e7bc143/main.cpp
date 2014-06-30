#include <iostream>
#include <string>
#include <iterator>
#include <vector>
#include <sstream>

int main(void)
{
    std::string input;
    std::getline(std::cin, input); // read a line
    std::istringstream in(input); // use input string stream to parse
    std::vector<int> numbers; // our array to be filled
    std::copy(std::istream_iterator<int>(in), std::istream_iterator<int>(), std::back_inserter(numbers));
    
    std::cout << "Numbers: ";
    std::copy(std::begin(numbers), std::end(numbers), std::ostream_iterator<int>(std::cout));
    std::cout << std::endl; // New line
    
   
}