#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

int main()
{
    
    std::srand(static_cast<int>(std::time(0)));
    
    std::vector<std::vector<char>> displayarray(5, std::vector<char>(5, '?'));
    std::vector<std::vector<char>> minearray(5, std::vector<char>(5, '0'));
    std::vector<std::vector<int>> guessedarray(5, std::vector<int>());
    
    int noofmines = 5;
    
    for (int i = noofmines; --i;) {
        
    }
    
}