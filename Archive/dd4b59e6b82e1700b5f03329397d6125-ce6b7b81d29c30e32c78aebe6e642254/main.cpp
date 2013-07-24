#include <iostream>

signed int s1 = -4;
unsigned int u1 = 2;

signed long long s2 = -4;
unsigned int u2 = 2;

signed int s3 = -4;
unsigned long long u3 = 2;

signed long long s4 = -4;
unsigned long long u4 = 2;

signed int s5 = -2;
unsigned int u5 = 4;

signed long long s6 = -2;
unsigned int u6 = 4;

signed int s7 = -2;
unsigned long long u7 = 4;

signed long long s8 = -2;
unsigned long long u8 = 4;

int main()
{
    std::cout << (s1 + u1) << "\n"; // 4294967294
    std::cout << (s2 + u2) << "\n"; // -2
    std::cout << (s3 + u3) << "\n"; // 18446744073709551614
    std::cout << (s4 + u4) << "\n"; // 18446744073709551614  
    std::cout << (s5 + u5) << "\n"; // 2  
    std::cout << (s6 + u6) << "\n"; // 2   
    std::cout << (s7 + u7) << "\n"; // 2  
    std::cout << (s8 + u8) << "\n"; // 2  
}