#include <iostream>
#include <vector>
#include <array>

using namespace std;

int main(){
    std::vector<int> v { { 42, 23, 1, 0, 9, 12 } };
    std::array<float, 4> a{ { 0.1, .5, 5., 4. } };
    
    for(auto& i : v) std::cout<<i<<' ';
    std::cout<<std::endl;
    
    for(auto& f : a) std::cout<<f<<' ';
    std::cout<<std::endl;
}

