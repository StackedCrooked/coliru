#include <iostream>
#include <vector>
 
int main(int argc, char * argv[]) 
{
    std::vector<std::string> everything(argv, argv + argc);
    std::cout << "Everything: ";
    for (auto e : everything) std::cout << e << '|';
    std::cout << '\n';
    
    std::vector<std::string> arguments(argv + 1, argv + argc);
    std::cout << "Arguments: ";
    for (auto arg : arguments) std::cout << arg << '|'; 
    std::cout << '\n';
}
