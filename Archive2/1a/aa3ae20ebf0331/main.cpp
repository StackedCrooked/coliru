#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int countNum(int n){
    return (n >= 10)
        ? 1 + countNum(n/10)
        : 1;
}

int main() {
    std::cout << countNum(0) << '\n';
    std::cout << countNum(1) << '\n';
    std::cout << countNum(5) << '\n';
    std::cout << countNum(197) << '\n';
    std::cout << countNum(59345) << '\n';
}
