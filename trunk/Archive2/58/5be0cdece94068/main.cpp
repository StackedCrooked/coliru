#include<random>
#include<limits>
#include <iostream>
int main(){
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> d(0, std::numeric_limits<double>::min());
    
    for(int i = 0; i < 10000; i++){
        double e;
        if((e = d(rng)) > 0) {
            std::cout << e << '\t' << std::numeric_limits<double>::min() << std::endl;
            break;
        }
    }
}