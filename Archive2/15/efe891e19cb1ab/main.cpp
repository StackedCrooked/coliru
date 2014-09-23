#include <iostream>
#include <array>
#include <string>

int main()
{
    std::array<std::string, 4> words = { "banane", "pomme", "poire", "orange" };
    for(auto& word : words)
    {
        printf("%-*.*s|\n", 15, 15, word.c_str());
    };
    
    return 0;
}