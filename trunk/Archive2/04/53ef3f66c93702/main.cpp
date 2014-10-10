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
    for (int n = 0; n < 10000; ++n) {
        int sum = 0;
        for (int p = 0; p < 10; ++p) {
            sum += (d(gen)-1) * std::pow(5, p);
        }
        sum %= static_cast<int>(std::pow(7, 7));//discard highest bit
        for (int p = 6; p >= 0; --p) {
            int div = std::pow(7, p);
            int res = sum / div + 1;
            //std::cout << sum << " " << div << " " << res << std::endl;
            sum %= div;
            ++hist[res];
        }
        
    }
    for (auto p : hist) {
        std::cout << p.first << ' ' << std::string(p.second/200, '*') << '\n';
    };
}