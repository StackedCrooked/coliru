#include <iostream>
#include <vector>
#include <tuple>
#include <memory>
#include <iomanip>

int main()
{
    std::vector< std::pair<int,char> > pairVector { {0,'a'}, {1,'b'}, {2,'c'}, {3,'d'}, {4,'e'} };

    // http://en.cppreference.com/w/cpp/memory/unique_ptr
    // http://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique
    auto storage = std::make_unique< char[] >( pairVector.size() ) ; // C++14
    // std::unique_ptr< char[] > storage( new char( pairVector.size() ) ) ;

    for( std::size_t i=0; i < pairVector.size(); ++i ) storage[i] = std::get<1>( pairVector[i] ) ;
    // or: for( std::size_t i=0; i < pairVector.size(); ++i ) storage[i] = pairVector[i].second ;

    std::cout << "The dynamic array contains ...:\n";
    std::cout << "Index    Value\n" ; // << endl;
    std::cout << "-----    -----\n" ; // << endl;

    for( std::size_t i=0; i < pairVector.size(); ++i )
        std::cout << i << std::setw(9) << storage[i] << '\n' ;
}
