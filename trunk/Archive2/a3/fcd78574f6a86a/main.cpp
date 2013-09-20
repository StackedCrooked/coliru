#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
 
int main(int, char**) {
    std::random_device rseed;
    std::mt19937 rng(rseed());
    
    std::vector<int> v(100);//reserve 100 elems
    
    for(int i = 0; i < 100; ++i) v[i] = i;//add values
    
    for(auto& elem : v) std::cout << elem << " ";//print values
    std::cout << "\n";
    
    std::shuffle(std::begin(v), std::end(v), rng);
    
    for(auto& elem : v) std::cout << elem << " ";//print values
    std::cout << "\n";
    
    std::sort(std::begin(v), std::end(v));
    
    for(auto& elem : v) std::cout << elem << " ";//print values
    std::cout << "\n";
    
    std::cout << std::endl;
}