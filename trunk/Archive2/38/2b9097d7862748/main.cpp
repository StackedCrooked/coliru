#include <iostream>
#include <string>
#include <map>
#include <random>
 
int main()
{
    std::random_device rd;
    std::map<int, int> hist;
    std::uniform_int_distribution<int> dist(0, 9);
    std::mt19937 randEngine(rd());
    
    for (int n = 0; n < 20000; ++n) { ++hist[dist(randEngine)]; }
    for (auto p : hist) {
        std::cout << p.first << " : " << std::string(p.second/100, '*') << '\n';
    }
}