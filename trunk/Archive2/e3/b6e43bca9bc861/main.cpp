#include <iostream>
#include <cmath>

int main() {    
    int denominator = 1;
    int numerator  = 1;
     
    //Don't use 0's here
    for (int i = 1; i < 10; i++) {
        for (int j = 1; j < i; j++) {
            for (int k = 1; k < j; k++) {
                
                const int first = (k * 10 + i) * j;
                const int second = k * (i * 10 + j);
                
                if (first == second) {
                    denominator *= j;
                    numerator  *= k;
                }
            }
        }
    }
    std::cout << numerator  << "/" << denominator << std::endl;
}
    