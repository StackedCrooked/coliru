    #include <iostream>
    #include <random>
    #include <cmath>
    
    int main()
    {
        std::random_device rd;
    
        std::mt19937_64 e2(rd());
    
        std::uniform_int_distribution<long long int> dist(std::llround(std::pow(2,61)), std::llround(std::pow(2,62)));
    
        std::cout << std::llround(std::pow(2,61)) << std::endl; 
        std::cout << std::llround(std::pow(2,62)) << std::endl; 
    
        for (int n = 0; n < 10; ++n) {
                std::cout << dist(e2)<< ", " ;
        }
        std::cout << std::endl ;
    }