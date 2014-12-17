#include <iostream>

auto greaterThan = [](int number) 
                   { return [number](int& value) { return value > number; }; };
                   
template <class Validate>
void myFun(int value, Validate validate)
{
    if (validate(value)) std::cout << "Valid!" << std::endl;
    else std::cout << "Not valid!" << std::endl;
}

int main()
{
    myFun(5, greaterThan(6));
    myFun(10, greaterThan(6));
}