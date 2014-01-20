#include <bitset>
#include <iostream>

int main() {
    std::bitset<32> x(146146713);
    std::cout << x.to_string() << '\n';
    std::bitset<8> y(x.to_string().substr(2, 8));
    std::cout << y.to_string() << '\n';
}
    
    