#include <iostream>
#include <tuple>
#include <utility>
#include <type_traits>
#include <functional>

/*template <typename T>
struct xrange {
    
    
};*/

int main ( int argc, char** argv ) {
	
    auto results = [ ( x * x ) | (1, 20) | (x * x > 144) ] ;
    std::cout << "[ ";
    for ( auto& result : results ) {
        std::cout << result << ' ';
    }
    std::cout << "]";
    
}