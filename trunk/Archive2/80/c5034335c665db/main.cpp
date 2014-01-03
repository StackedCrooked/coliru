#include <cstddef>
#include <type_traits>
#include <vector>
#include <iostream>

// struct and class are EXACTLY the same, one just defaults to all members being public by default (struct)
// all class members by default until you declare them public are private
struct GameObject {
    
    virtual void DoShit () {
        std::cout << "Game Object" << std::endl;
    }
    
};

struct Goal : public GameObject {
    
    virtual void DoShit () {
        std::cout << "Goal" << std::endl;
    }
    
};

struct Player : public GameObject {
    
    virtual void DoShit () {
        std::cout << "Player" << std::endl;
    }
    
};

int main( ) {
    
    std::vector<GameObject> objects;
    GameObject gameobject{}; // Constructed objects
    Goal goal{};
    Player player{};
    objects.push_back( gameobject );
    objects.push_back( goal ); // SLICED
    objects.push_back( player ); // SLICED
    
    for ( std::size_t i = 0; i < objects.size(); ++i ) {
        objects[i].DoShit();
    }
    std::cout << "If you see three game objects, you've just experienced Slicing." << std::endl;
}