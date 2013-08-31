#include<iostream>
#include<iomanip>
#include <string>

class Vehicle
{
public:
        

        class Car
        {
                public:
                    std::string name;
        };
        
        static Car* createCar()
        {
                return new Car;
        }

        
private:
        int seats;

};

void useVehicle()
{

Vehicle::Car *c = Vehicle::createCar();
c->name = "BMW";
}

int main(int argc, char *argv[])
{
useVehicle();
return 0;
}
