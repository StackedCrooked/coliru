#include <iostream>

template <class MapT>
struct Tile {
    void dontCallMe() {
        static_assert(false, "Told you !");
        std::cout << "Trap failed\n";
    }
};

int main()
{
    Tile<int const> boom;
    
    //boom.dontCallMe();
    
    return 0;
}
