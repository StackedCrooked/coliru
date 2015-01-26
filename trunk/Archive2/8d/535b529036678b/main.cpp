#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
    std::vector<int> source(11);
    std::vector<int> target;
    
    std::iota(source.begin(), source.end(), -5);
    
    for( auto& el : source )
        std::cout << el << ' ';
    std::cout << '\n';
    
    std::copy_if( source.begin(), source.end(), std::back_inserter(target), []( const int i ) { return i%2; } );
    
    for( auto& el : target )
        std::cout << el << ' ';
    std::cout << '\n';
    
}
