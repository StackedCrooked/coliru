#include <iostream>

class MyInteger
{
public:
    MyInteger(int number) : number(number) {}
    operator int() const { return ( number ); }

private:
    int number;
};

int main()
{
    MyInteger my_integer(42);
    std::cout << my_integer << std::endl;
}