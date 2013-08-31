#include <iostream>
#include <sstream>
#include <string>
    
    
int main()
{   
    std::istringstream fake_cin("your mom is fat");
    
    std::cout << "\nPlease enter a word:" << std::endl;
    std::string word;
    while (fake_cin >> word)
    {
        std::cout << word << std::endl;
        std::cout << "\nPlease enter a word:" << std::endl;        
    }    
}
