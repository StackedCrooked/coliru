#include <iostream>
#include <vector>

// (all doubles for exposition)
struct Car
{
    double size;
    double weight;
    double color;
    double id;
};

typedef double Car::*ptrToCarMember;

double measureSim(const Car& a, const Car& b, std::vector<ptrToCarMember> feature)
{
    double value = 0;
    
    for (auto el : feature) {
        value += a.*el - b.*el;
    }
    
    return value;
}

int main()
{
    Car a = { 1.0, 2.0, 4.0, 8.0 };
    Car b = { 1.0, 2.0, 3.0, 4.0 };
    
    {
        std::vector<ptrToCarMember> features{&Car::size};
        std::cout << measureSim(a, b, features) << '\n';
    }
    
    {
        std::vector<ptrToCarMember> features{&Car::id};
        std::cout << measureSim(a, b, features) << '\n';
    }
    
    {
        std::vector<ptrToCarMember> features{&Car::size, &Car::weight, &Car::color};
        std::cout << measureSim(a, b, features) << '\n';
    }
}
