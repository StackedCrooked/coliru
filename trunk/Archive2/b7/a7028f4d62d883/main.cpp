#include <iostream>
#include <chrono>
#include <random>

int main()
{
    std::default_random_engine generator( std::random_device{}() ) ;
    // or, if we do not have a true std::random_device: 
    // const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count() ;
    // std::default_random_engine generator(seed) ;
    
    std::normal_distribution<double> distribution1(0.1,3.0);

    const int n = 1000000 ;
    double sum = 0 ;
    for( int i = 0 ; i < n ; ++i ) sum += distribution1(generator) ;
    std::cout << sum / n << '\n' ;
}
