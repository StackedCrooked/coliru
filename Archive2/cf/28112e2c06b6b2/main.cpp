#include <vector>
#include <random>
#include <iostream>
#include <algorithm>
#include <numeric>

int main()
{
    std::default_random_engine generator (10);
    std::vector<int> v(10);
    
    iota(begin(v), end(v), 0);
    shuffle(begin(v), end(v), generator);
    
    for (auto x : v) { std::cout << x; }
}