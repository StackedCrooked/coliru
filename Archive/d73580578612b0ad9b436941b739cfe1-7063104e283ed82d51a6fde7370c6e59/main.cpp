#include <iostream>

class player {
public:
    enum direction { north, east, south, west };

    void move(direction d) {
        switch (d) {
            case north:
                std::cout << "going north" << std::endl;
                break;
            case east:
                std::cout << "going east" << std::endl;
                break;
            case south:
                std::cout << "going south" << std::endl;
                break;
            case west:
                std::cout << "going west" << std::endl;
                break;
            default:
                std::cout << "the sky is the limit" << std::endl;
        }
    }
};

int main()
{
    player p;                                                                                            
    p.move(player::west);
}
