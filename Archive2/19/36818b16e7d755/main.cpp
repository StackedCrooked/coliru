#include <iostream>

int main() {
    int input = 4;
    
    switch (input) {
    do {
        std::cout << input;
        input -= 100; 
        
        break;
        
        default: std::cout << input;
        
    } while (input);
    }
}