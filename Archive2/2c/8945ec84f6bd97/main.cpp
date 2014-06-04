#include <iostream>
#include <chrono>
#include <gmpxx.h>


void UsingModulo() {
    for (int i = 0; i < 1000000; i++) {
        mpz_class num = 1120390317;
        mpz_class sum = 0;
        
        while(num != 0) {
            mpz_class rem = (num % 10);
            sum = sum + rem;
            num = num / 10;
        }
    }
}


void UsingString() {
    for (int i = 0; i < 1000000; i++) {
        mpz_class num = 1120390317;
        mpz_class sum = 0;
        
        const std::string strNum = num.get_str();
        for (auto c : strNum) {
            sum += c - '0';
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
