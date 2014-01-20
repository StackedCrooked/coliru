#include <iostream>
#include <string>
#include <algorithm>

int Remover(const std::string number) {
    std::string temp = "";
    
    if (number.find('0') != 0) {
        temp += number[0];
    }
    temp += number[1];
    temp += number[2];
    return std::stoi(temp);
}

int main() {
    unsigned long long solution = 0;
    
    int digits[] = { 0,1,2,3,4,5,6,7,8,9 };
    int divisors[] = { 2,3,5,7,11,13,17 };
    
    while (std::next_permutation(digits,digits + 10)) {
    
        std::string permutate = "";
        for (const auto e : digits) {
            permutate += std::to_string(e);
        }
    
        const int div2 = Remover(std::to_string(digits[1]) + std::to_string(digits[2]) + std::to_string(digits[3]));
        const int div3 = Remover(std::to_string(digits[2]) + std::to_string(digits[3]) + std::to_string(digits[4]));
        const int div5 = Remover(std::to_string(digits[3]) + std::to_string(digits[4]) + std::to_string(digits[5]));
        const int div7 = Remover(std::to_string(digits[4]) + std::to_string(digits[5]) + std::to_string(digits[6]));
        const int div11 = Remover(std::to_string(digits[5]) + std::to_string(digits[6]) + std::to_string(digits[7]));
        const int div13 = Remover(std::to_string(digits[6]) + std::to_string(digits[7]) + std::to_string(digits[8]));
        const int div17 = Remover(std::to_string(digits[7]) + std::to_string(digits[8]) + std::to_string(digits[9]));
        
        int divisions[] = { div2, div3, div5, div7, div11, div13, div17 };
        
        bool shouldBreak = false;
        for (int i = 0; i < 7; i++) {
            if (divisions[i] % divisors[i] != 0) {
                shouldBreak = true;
            }
        }
                
        
        if (!shouldBreak) {
            solution += std::stoull(permutate);
        }
    }

    std::cout << "Solution: " << solution << std::endl;
}