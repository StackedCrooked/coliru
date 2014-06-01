#include <iostream>
#include <chrono>
#include <gmpxx.h>


/**
 * Program to calculate sum and product over a number
 */

void UsingModulo() {
    mpz_class rem;
    mpz_class num = 1120390317;
    unsigned int sum = 0;
    unsigned int pro = 1;
    
    for (int i = 0; i < 1000000; i++) {
        num = 1120390317;
        sum = 0;
        pro = 1;
        
        __mpz_struct *q = num.get_mpz_t();
        while(*(q->_mp_d) != 0) {
            auto digit = mpn_divrem_1 (q->_mp_d, (mp_size_t) 0, 
                    q->_mp_d, q->_mp_size, (mp_limb_t) 10);
            sum += digit;
            pro *= digit;
        }
        
    }
}


void UsingString() {
    mpz_class num;
    unsigned int sum;
    unsigned int pro;
    
    for (int i = 0; i < 1000000; i++) {
        num = 1120390317;
        sum = 0;
        pro = 1;
        
        const std::string strNum = num.get_str();
        for (auto c : strNum) {
            int res = c - '0';
            sum += res;
            pro *= res;
        }
    }
}


int main() {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    UsingModulo();
    
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds1 = end - start;
    start = std::chrono::system_clock::now();
    
    UsingString();
    
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds2 = end - start;
    
    std::cout << "Modulo: " << elapsed_seconds1.count() << " seconds" << std::endl;
    std::cout << "String: " << elapsed_seconds2.count() << " seconds" << std::endl;
}
