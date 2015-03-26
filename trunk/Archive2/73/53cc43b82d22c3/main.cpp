#include <vector>
#include <iostream>

int main() {
    std::vector<int> numbers = {5,6,7}; //size is 3
    int i = -1; 
    std::cout << i % 3 <<"\n";                  // output: -1
    std::cout << i % numbers.size() << "\n";    // output: 0
}