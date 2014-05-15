#include <iostream>
#include <cstdint>

//static std::uint_fast32_t input[80][80];


int main () {
    std::uint_fast64_t solution;
    
    for (int i = 78; i >= 0; i--) {
        for (int j = 0; j < 80; j++) {
            solution = input[j][i + 1];
            
            for (int k = j + 1, l = 0; k < 80; k++) {
                if (l + input[k][i] >= solution) {
                    break;
                }
                
                if (input[k][i] + input[k][i + 1] + l < solution) {
                    solution = l + input[k][i] + input[k][i + 1];
                }
                l += input[k][i];
                
            }
            
            if(input[j - 1][i] < solution && j > 0) {
                solution = input[j - 1][i];
            }
            
            input[j][i] += solution;
        }
    }
    
    for (int i = 1; i < 80; i++) {
        if (input[i][0] < solution) {
            solution = input[i][0];
        }
    }
    
    std::cout << "Solution: " << solution;
}