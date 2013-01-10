#include <iostream>
#include <cmath>
#include <set>

int main() {
    std::set<double> sets;
    for(double a = 2; a <= 100; a++) {
        for(double b = 2; b <= 100; b++) {
            sets.insert(std::pow(a,b));
        }
    }
    std::cout << sets.size();
}