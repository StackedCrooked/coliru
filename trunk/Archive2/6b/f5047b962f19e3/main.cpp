#include <string>
#include <vector>
#include <sstream>
#include <iostream>

int main()
{
    std::vector<std::string> strings { "1", "2", "3", "42", "1337" };
    std::vector<int> numbers(strings.size());
    
    
    for (std::size_t i = 0; i < strings.size(); i++) {
        std::stringstream(strings[i]) >> numbers[i];
    }
    
    for (std::size_t i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << ' ';
    }
    
    return 0;
}

