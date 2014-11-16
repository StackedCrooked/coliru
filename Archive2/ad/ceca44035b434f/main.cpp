#include <iostream>

class X
{
    void xx();
    
public:

    X() {xx();}
};

class Y
{
    friend X;
    
    void yy() { std::cout << "Y::yy()\n"; }
};

void X::xx()
{
    std::cout << "X::xx()\n";
    Y y;
    y.yy();
}

int main()
{
    X x;
}