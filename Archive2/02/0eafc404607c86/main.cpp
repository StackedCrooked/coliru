#include <iostream>

struct Tracked
{
    Tracked() { std::cout << "Tracked()\n"; }
    ~Tracked() { std::cout << "~Tracked()\n"; }
};

int main()
{
    size_t i = 0;
    
again:
    Tracked t;
    
    if (i++ < 5)
        goto again;
}
