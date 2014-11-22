#include <iostream>

int main()
{
    char small[26];
    char big[26];
    
    for(int i = 65; i < 65+26; ++i) {
        small[i-65] = i;
        big[i-65] = i+6+26;
        
        std::cout << ((i-65) % 2 ? small[i-65] : big[i-65]);
    }
    std::cout << std::endl;
    
    for(int i = 0; i < 26; ++i) {
        std::cout << (i % 2 ? big[i] : small[i]);
    }
}
