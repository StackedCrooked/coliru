#include <iostream>
#include <string>
#include <vector>

class Move {
public:
    Move() : i(nullptr)
    {
        std::cout << "Default constructor" << std::endl;
    }
    Move(const Move& o)
    {
        std::cout << "Copy constructor" << std::endl;
        i = new int(*o.i);
    }
    ~Move()
    {
        delete i;
        std::cout << "destructor" << std::endl;
    }
    
    int* i;
};

Move GetTemp()
{
    Move temp = Move();
    std::cout << "GetTemp" << std::endl;
    return temp;
}

int main()
{
    Move m(GetTemp());
}
