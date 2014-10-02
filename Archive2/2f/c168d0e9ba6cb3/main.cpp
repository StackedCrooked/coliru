#include <iostream>

struct X {
    virtual ~X() = 0;
};
struct Y : X {};

X::~X() {std::cout << "Ha!\n";}
    

int main()
{
    Y y;
}
