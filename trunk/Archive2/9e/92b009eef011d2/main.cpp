#include <iostream>

struct t
{
    int x;
    int& y = x;
};

int main()
{
    t t1;   // can't brace-initialise it, though
    t1.x = 3;
    
    std::cout << t1.y << '\n';
}
 