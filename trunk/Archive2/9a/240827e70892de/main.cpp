#include <iostream>
#include <string>
#include <vector>


class Test {
public:
    Test() { std::cout << "Test()" << std::endl; } 
    Test(int) { std::cout << "Test(int)" << std::endl; }
    
    Test& operator=(const Test&) { std::cout << "operator=(const Test&)" << std::endl; return *this; }
    
    Test& operator=(int) { std::cout << "operator=(int)" << std::endl; return *this; }
};


int main() {
    Test t;
    t = {};     // :(
    t = {1};
}
