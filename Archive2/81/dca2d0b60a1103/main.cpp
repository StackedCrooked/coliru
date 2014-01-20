#include <iostream>

int main() {    
    long solution = 1;
 
    for (int i = 0; i < 20; i++) {
        solution = solution * ((2 * 20) - i);
        solution =  solution / (i + 1);
    }
    std::cout << "Solution: " << solution;
}