#include <iostream>
#include <memory>
#include <iomanip>

int main()
{
    constexpr std::size_t TESTSZ = 32 * 1000 * 1000 ;
    constexpr std::size_t UBSZ = 21 ;

    std::srand( std::time(0) ) ;
    std::size_t nauto = 0 ;
    std::size_t ndyn = 0 ;
    std::cout << std::fixed << std::setprecision(2) ;
    
    auto begin_auto = clock() ;

    // create, access and destroy 32 million strings (average size: 10 characters)
    {
        for( std::size_t i = 0 ; i < TESTSZ ; ++i )
        {
            std::string str( std::rand() % UBSZ, ' ' ) ;
            nauto += str.size() ;
        }
    }
    auto end_auto = clock() ;

    // create, access and destroy 32 million strings (average size: 10 characters)
    {
        for( std::size_t i = 0 ; i < TESTSZ ; ++i )
        {
            std::unique_ptr<std::string> ptr( new std::string( std::rand() % UBSZ, ' ' ) ) ;
            ndyn += ptr->size() ;
        }
    }
    auto end_dynamic = clock() ;
    
    std::cout << "automatic: " << double( end_auto - begin_auto ) / CLOCKS_PER_SEC << " secs  "
              << "average size: " <<  double(nauto) / TESTSZ << '\n'
              << "  dynamic: " << double( end_dynamic - end_auto ) / CLOCKS_PER_SEC << " secs  " 
              << "average size: " <<  double(ndyn) / TESTSZ << '\n' ;
}
