#include <iostream>
#include <string>
#include <vector>

struct A {
    int getI() { return i; }
    
private:
    static int i;
};

int A::i = 42;

int main()
{
    A* a = 0;
    
    std::cout << "i = " << a->getI() << std::endl;
}
