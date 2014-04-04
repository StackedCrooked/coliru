#include <iostream>

class T {};
class U { U() = delete; };

int main() {
    decltype(new T{}) durr;
    // decltype(new U{}) hurr;
    std::cout<<"Hello world."<<std::endl;    
}