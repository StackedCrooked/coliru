#include <iostream>
#include <cmath>
#include <algorithm>

bool Pentagon(const int number) {
    const int numberShift = floor((std::sqrt(1.0 + 24 * number) + 1) / 6);
    return ((std::sqrt(1.0 + 24 * number) + 1) / 6 - numberShift) < std::numeric_limits<double>::epsilon();
}

int main() { 
    int solution = 0;
    int i = 200;
    
    while (true) {
        if (Pentagon(solution)) {
            break;
        }
        
        solution = i * (2 * i - 1);
        i++;        
    }
    std::cout << "Solution: " << solution << std::endl;
}