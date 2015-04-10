#include <random>
#include <iostream>
 
int main()
{
    std::default_random_engine gen;
    std::uniform_real_distribution<double> dis(0, 1);
    
    int lt_pfive(0), gte_pfive(0);
    
    for (int n = 0; n < 100000000; ++n) {
        if ( dis(gen) >= 0.5) { gte_pfive++; }
        else {lt_pfive++;}
    }
    
    std::cout << lt_pfive << " " << gte_pfive << std::endl;
}