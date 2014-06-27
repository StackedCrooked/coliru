#include <iostream>

enum type
    { none              = 0
    , scene             = 1 << 0
    , player_aircraft   = 1 << 1
    , allied_aircraft   = 1 << 2
    , enemy_aircraft    = 1 << 3 };

int main() {
    auto a = scene;
    auto b = enemy_aircraft;
    auto c = player_aircraft;
    
    std::cout << "a is of type: " << ((a & scene) ? "scene" : "not scene") << '\n';    
    std::cout << "b is of type: " << ((b & enemy_aircraft) ? "enemy_aircraft" : "not enemy_aircraft") << '\n'; 
    std::cout << "c is of type: " << ((c & player_aircraft) ? "player_aircraft" : "not player_aircraft") << '\n'; 
}