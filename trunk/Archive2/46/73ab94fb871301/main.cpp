#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
 
int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    // perform 4 trials, each succeeds 1 in 2 times
    std::uniform_int_distribution<> d(1, 5);
 
    std::map<int, int> hist;
    for (int n = 0; n < 100000; ++n) {
        int sum = (d(gen)-1) + (d(gen)-1) + (d(gen)-1) + (d(gen)-1) + (d(gen)-1) + (d(gen)-1);
        sum %= 7;
        ++sum;
        ++hist[sum];
    }
    for (auto p : hist) {
        std::cout << p.first << ' ' << std::string(p.second/100, '*') << '\n';
    }
}