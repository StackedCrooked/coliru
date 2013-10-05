#include <iostream>

struct my_class {
    my_class() { 
        std::cout << "Default constructed\n";
    }
    
    ~my_class() {
        std::cout << "Destroyed\n";
    }
};

int main() {
    my_class lol;
}