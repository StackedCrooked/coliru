#include <vector>
#include <map>
#include <iostream>
#include <iomanip>

int main()
{
    std::vector<double> vec = 
    {
        3.25, 2.54, 2.00, 2.54, 3.25,
        2.54, 1.70, 1.00, 1.70, 2.54,
        2.00, 1.00, 0.00, 1.00, 2.00,
        2.54, 1.70, 1.00, 1.70, 2.54,
        3.25, 2.54, 2.00, 2.54, 3.25
    };
    
    std::map<double, int> map;
    
    for (auto n : vec) {
        map[n]++;
    }
    
    for (auto p : map) {
        std::cout << std::fixed << std::setprecision(3)
                  << p.first << " occurs " << p.second << " times\n";
    }
}