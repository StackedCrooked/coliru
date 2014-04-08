#include <string>
#include <iostream>
#include <algorithm>

int main() {
    auto fun = [](char i) { return (i >= 'a' && i <= 'z'); };
    std::string name = "test";
    std::string not_name = "!";
    std::cout << std::all_of(name.begin(), name.end(), fun);
    std::cout << std::all_of(not_name.begin(), not_name.end(), fun);
}