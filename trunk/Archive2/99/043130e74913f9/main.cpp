#include <iostream>

struct someobject {};

int main () {
    someobject* scratchpad[10][10] = {};
    int j = 0;
    
    
    unsigned index = ++reinterpret_cast<unsigned&>(scratchpad[j][0]);
    
    std::cout << index;
}