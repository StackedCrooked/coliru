#include <iostream>


class Base
{
public:
    Base() = default;
    Base( int , int , int ) : Base{}
    {
        std::cout << "Hello!" << std::endl;
    }
};

class Derived : public Base
{
public:
    using Base::Base; //Automatically adds all the base constructors
};

int main()
{
    Derived d{ 1 , 1 , 1 };
}