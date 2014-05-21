#include <cmath>
#include <iostream>

int main() {
    int solution = 0;
    const int limit = 1000000;
    
    for (int i = 0, m = 1;; m++) {
        int current = 0;
        
        for (int j = 1; j < m; j++) {
            for (int k = j; k < m; k++) {
                const int first  = k + m;
                const int second = j + m;
                const int third  = j + k;
                
                const int sums[3] = {
                    j * j + first * first,
                    k * k + second * second,
                    m * m + third * third
                };
                
                int min = (sums[1] < sums[0]) ? sums[1] : sums[0];
                if (sums[2] < min) {
                    min = sums[2];
                }
                
                //! Check for integer
                const int sqrtMin = std::sqrt(min);
                if (sqrtMin * sqrtMin == min) {
                    current++;    
                }
            }
        }
        
        if (i + current > limit) {
            solution = m - 2;
            break;
        }
        i += current;
    }
    std::cout << "Solution: " << solution << std::endl;			
}