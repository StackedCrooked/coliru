#include <iostream>
#include <cstdint>

using std::int64_t;
constexpr int64_t COIN = 100'000'000;

int64_t calculate_subsidy(int64_t nHeight) {
    int64_t nSubsidy = 50 * COIN;
    nSubsidy >>= (nHeight / 210'000);
    return nSubsidy;
}
    
int main() {    
    std::cout << calculate_subsidy(0 * 210'000) << '\n';
    std::cout << calculate_subsidy(1 * 210'000) << '\n';
    std::cout << calculate_subsidy(2 * 210'000) << '\n';
    
    std::cout << calculate_subsidy(64 * 210'000 - 1) << '\n';
    std::cout << calculate_subsidy(64 * 210'000) << '\n';
    std::cout << calculate_subsidy(65 * 210'000) << '\n';
    std::cout << calculate_subsidy(66 * 210'000) << '\n';
}