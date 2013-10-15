#include <iostream>

int volume = 0;
class Box
{
    public:
        Box ()
        {
            std::cout<<++volume;
        }
        ~Box()
        {
        std::cout<<volume--;
        }
};

int main ()
{
    Box object1,object2,object3;
    {
        Box object4;
    }
} 
