#include <iostream>
#include <bitset>
 
int main()
{
    std::bitset<8> b("00010010");
    std::cout << "initial value: " << b << '\n';
 
    // find the first unset bit
    size_t idx = 0;
    while (idx < b.size() && b.test(idx)) ++idx;
 
    // continue setting bits until half the bitset is filled
    while (idx < b.size() && b.count() < b.size()/2) {
        b.set(idx);
        std::cout << "setting bit " << idx << ": " << b << '\n';
        while (idx < b.size() && b.test(idx)) ++idx;
    }
 
}