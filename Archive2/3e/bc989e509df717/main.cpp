#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
 
using namespace std;
 
int main()
{
    std::vector<float> data = { 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 6, 6, 6, 7, 7, 7};
    vector<float> inverse = { 7, 7, 7, 6, 6, 6, 4, 4, 4, 3.5, 3, 3, 3, 2, 1, 1};
 
    //auto lower = std::lower_bound(data.begin(), data.end(), 5);
    //auto upper = std::upper_bound(data.begin(), data.end(), 5);
    
    auto l = std::lower_bound(inverse.begin(), inverse.end(), 2.5, [](float a, float b) { return a > b; } );
    auto u = std::upper_bound(inverse.begin(), inverse.end(), 3.5, [](float a, float b) { return a > b; } );
    
    //std::cout << "Pos: " << (lower - data.begin()) << " - Value: " << *lower << std::endl;
    std::cout << "Pos: " << (l - inverse.begin()) << " - Value: " << *l << std::endl;
    std::cout << "Pos: " << (u - inverse.begin()) << " - Value: " << *u << std::endl;

    //std::copy(lower, upper, std::ostream_iterator<int>(std::cout, " "));
}