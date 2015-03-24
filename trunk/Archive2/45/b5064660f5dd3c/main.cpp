#include <iostream>
#include <iomanip>
#include <bitset>

int main() {
    std::bitset<8> digit;
    std::cout << std::setfill('0') << std::hex;
    while (std::cin >> digit)
        std::cout << std::setw(2) << digit.to_ulong();
}
