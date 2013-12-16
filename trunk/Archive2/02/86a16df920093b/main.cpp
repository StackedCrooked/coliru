#include <iostream>
#include <vector>

using namespace std;

class animal 
{
    public:
        animal () {}
        void speak() {cout << "hi" ;}
};

int main()
{
    animal a;
    animal b;
    animal c;
    for ( animal * ptr : { &a , &b , &c } )
    {
        ptr->speak();
    }
}
