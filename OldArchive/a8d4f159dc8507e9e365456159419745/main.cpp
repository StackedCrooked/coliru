#include <iostream>
int main() {
    unsigned s[7] = {2,2,2,1,2,1,2};
    unsigned n = 0;  
    unsigned y = 1901;
    unsigned c = 0;
    for(; y < 2001; ++y) {
        c %= 7;
        n += s[c];
        c+= ((y%4!=0)||(y%400==0) ? 1 : 2);
    }
    std::cout << n << std::endl;
}