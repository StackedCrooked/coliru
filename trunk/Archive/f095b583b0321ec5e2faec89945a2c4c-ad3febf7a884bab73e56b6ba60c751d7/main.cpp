#include <iostream>
#include <future>

int main() {    
    
    void func();
    func();
}

void func () { 
    std::cout << "Hi" << std::endl; 
}