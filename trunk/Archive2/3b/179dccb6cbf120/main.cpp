#include <iostream>

bool Prime(int number){
    if (number == 1) {
        return false;    
    }
    if (number == 2) {
        return true;    
    }
    if (number % 2 == 0) {
        return false;
    }
    for (int i = 3; (i * i) <= number; i += 2){
        if (number % i == 0 ) { 
            return false;
        }
    }
    return true;
}

int main () {
    int solution = 0;
    int currentCheck = 1000000;

    while (true) {
        for (int i = 1; i < 1000000; i++) {
            if (Prime(i)) {           
                if (solution + i < currentCheck) {
                    solution += i;    
                }
                else {
                    currentCheck = solution;
                    break;
                }
            }
        }
        if (Prime(solution)) {
            break;
        }
    }
    
    
    

    std::cout << "Solution: " << solution << std::endl;
}