#include <iostream>
#include <iomanip>
#include <vector>

void grow( std::vector<int>& vec, std::size_t n )
{
    std::cout << "initial size: " << std::setw(2) << vec.size() 
              << " capacity: " << std::setw(2) << vec.capacity() << '\n' ;
              
    auto buffer = vec.data() ;
    
    for( std::size_t i = 0 ; i < n ; ++i )
    {
        vec.push_back(i) ;
        
        if( buffer != vec.data() )
        {
            std::cout << "relocated to a larger buffer.  size: " << std::setw(2) << vec.size() 
                      << " capacity: " << std::setw(2) << vec.capacity() << '\n' ;
                      
            buffer = vec.data() ;
        }
    }

    std::cout << " final size: " << std::setw(2) << vec.size() 
              << " capacity: " << std::setw(2) << vec.capacity() << '\n' ;
}

int main()
{
    std::cout << "\n-------- with reserve --------\n" ;
    {
        std::vector<int> vec ;
        vec.reserve(100) ; // reserve space for up to 100 elements 
        grow( vec, 100 ) ;
    }

    std::cout << "\n-------- without reserve --------\n" ;
    {
        std::vector<int> vec ;
        grow( vec, 100 ) ;
    }
}
