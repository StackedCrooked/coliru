#include <iostream>
#include <string>
#include <vector>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


int main()
{
    std::string input;
    while (std::getline(std::cin,input)) {
		parser.get_command(input);
        std::cout << parser.command << std::endl;
	}
    
    // change to
    while(std::getline(std::cin, parser)) {
        std::cout << parser <<std::endl;
    }
}
