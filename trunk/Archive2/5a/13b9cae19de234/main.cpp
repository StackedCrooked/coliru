#include <iostream>

enum class PaintColor{
 BLACK=0,
 PINK=1,
 ORANGE=2
};

enum class Vehicle : char{ //Vehicle is 1 byte size
 CAR=0,
 JET=1,
 BOAT=2
};

int main() {
    PaintColor p;
    p = PaintColor::PINK;
    
    Vehicle v;
    v = Vehicle::BOAT;
    
    std::cout << (int)p << std::endl; 
    std::cout << (int)v<< std::endl; 
       std::cout << sizeof(v)<< std::endl; 
}