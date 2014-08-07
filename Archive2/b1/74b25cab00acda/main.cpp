#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cassert>

unsigned biggerpower(unsigned value, unsigned base) 
{
    unsigned result = 1;
    while(value > result) result*=base;
    return result;
}

unsigned rotatenumber(unsigned n, unsigned rotate_right_by) {
    int p = (int)pow(10, rotate_right_by); // if you want to rotate by 3 digits
    std::div_t d = std::div(n,p);
    int np = biggerpower(d.quot,10);
    int result = d.rem*np + d.quot;
    return result;
}

int main() {
    std::cout << rotatenumber(25314,3) << '\n';
    std::cout << rotatenumber(32546,4) << '\n';
}