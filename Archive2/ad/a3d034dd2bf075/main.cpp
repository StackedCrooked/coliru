#include <iostream>
#include <vector>
#include <numeric>

int sum_digits(int);



int main() {
    
    std::cout << sum_digits(1000) << std::endl;
    
    
    return 0;
 
 
    
}



int sum_digits(int e) {
    std::vector<int> digits(e);
    digits[0] = 1;
    int last_digit = 1;

    for (int power = 0; power < e; ++power) {
        int carry = 0;
        for (int idx = 0; idx < last_digit; ++idx) {
            int prod = digits[idx] * 2 + carry;
            if (prod > 9) {
                carry = 1;
                prod -= 10;
            }
            else {
                carry = 0;
            }
            digits[idx] = prod;
        }

        if (carry) {
            digits[last_digit++] = 1;
        }
    }

    // then just sum 'em  
    return std::accumulate(digits.begin(), digits.end(), 0);
}