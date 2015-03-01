#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct Player
{
    int id;
    std::string name;
};

int main()
{
    std::vector<Player> players = { { 0, "Foo" }, { 1, "Bar" }, { 2, "Baz" } };
    
    std::string name = "Bar";
    auto it = std::find_if(players.begin(), players.end(), [&](const Player& p) { return p.name == name; });
    
    if (it != players.end())
        std::cout << "Player found." << std::endl;
    else
        std::cout << "Player not found." << std::endl;
        
    return 0;
}