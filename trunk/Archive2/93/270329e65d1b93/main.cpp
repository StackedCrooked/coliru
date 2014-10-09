#include <iostream>
#include <string>
#include <map>
#include <random>
 
int main() {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> rng5(1, 5);

    std::map<int, int> hist;
    for (int n = 0; n < 100000; ++n) {
        int sum = (rng5(gen)-1) * 125 + (rng5(gen)-1) * 25 + (rng5(gen)-1) * 5 + (rng5(gen)-1);
        //int rest = sum % 7;
        sum %= 7;
        ++hist[sum+1];
    }
    for (auto p : hist) {
        std::cout << p.first << ' ' << std::string(p.second/100, '*') << '\n';
    }
}
