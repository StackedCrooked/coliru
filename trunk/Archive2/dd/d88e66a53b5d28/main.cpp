#include <iostream>
#include <map>
#include <random>
 
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d={40, 10, 10, 40};
    std::map<int, int> m;
    for(int n=0; n<10000; ++n) {
        ++m[d(gen)];
    }
    for(auto p : m) {
        std::cout << p.first << " generated " << p.second << " times\n";
    }
}