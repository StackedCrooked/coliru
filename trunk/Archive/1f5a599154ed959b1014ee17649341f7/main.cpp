#include <iostream>
#include <array>

class Class
{
private:
    int array[2];
public:
    Class() : array{2, 5} {}
    
    void printOut(int x)
    {
        std::cout << array[x];
    }
};

int main() {
    Class c;
    c.printOut(1);
}