#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
 
    std::lognormal_distribution<> d(1.6, 0.25);
 
    std::map<int, int> hist;
    for(int n=0; n<100; ++n) {
        hist[n] = d(gen);
    }
    for(auto p : hist) {
        std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                  << p.first << ' ' << p.second << '\n';
    }
}