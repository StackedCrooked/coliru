#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

enum En { nonnon = 1, biyori = 2 };

int main()
{
    std::unordered_map<En, std::string, std::hash<int>> um = { {nonnon, "nonnon"}, {biyori, "biyori"} };
    
    for( const auto& pa : um )
    {
        std::cout << pa.first << " = " << pa.second << std::endl;
    }
}
