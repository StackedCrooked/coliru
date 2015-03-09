#include <map>
#include <iostream>

struct A
{
    A( std::map<int,A> &m, int x ) : m_(m), x_(x) {} ;
    ~A()
    {
        for( const auto &elem : m_ )
        {
            std::cout << elem.second.x_ << std::endl ;
        }
    }
    
    
    std::map<int, A> &m_ ;
    int x_ = 0 ;
} ;

int main()
{
    std::map<int, A> m1;    
    
    m1.emplace( std::make_pair( 0, A( m1, 1 ) ) ) ;
    m1.emplace( std::make_pair( 1, A( m1, 2 ) ) ) ;
    m1.emplace( std::make_pair( 2, A( m1, 3 ) ) ) ;
    
    std::cout << "Done creating\n\n"  ;
    
    m1.erase( 1 ) ;
    
    std::cout << "\n\nDone erasing\n\n"  ;
    
    
}

