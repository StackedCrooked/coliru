#include <iostream>

int main() {    
    bool b = false;
    
    if (1<<63 == 0) {
        b = true;
    }
    
    std::cout << b;
}