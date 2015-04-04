#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
 
int main()
{
    std::vector<int> v = {1, 2};
 
    std::random_device rd;
    std::mt19937 g(rd());
 
    for (int i=0; i<10; ++i) {
        std::shuffle(v.begin(), v.end(), g);
 
        std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << "\n";
    }
}