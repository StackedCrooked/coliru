#include <iostream>
#include <string>
#include <vector>


struct A {
    int x;
};


int main() {
    class A A;
    A.x = 42;
    
    std::cout << A.x << std::endl;
}
