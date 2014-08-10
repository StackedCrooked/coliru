#include <iostream>
#include <utility>
#include <string>
#include <vector>

template < typename A, typename B > struct wrapper_t
{
     const A& first ;
     const B& second ;
};

template < typename A, typename B >
wrapper_t<A,B> wrap( const A& first, const B& second ) { return { first, second } ; }

template < typename SEQA, typename SEQB >
std::ostream& operator<< ( std::ostream& stm, const wrapper_t<SEQA,SEQB>& wrapper )
{
    for( std::size_t i = 0 ; i < wrapper.first.size() ; ++i )
        stm << wrapper.first[i] << ", " << wrapper.second.at(i) << '\n' ;
    return stm ;
}

int main()
{
    const std::vector<std::string> names { "felix", "fido", "silver", "daffy", "button" } ;
    const std::vector<double> ages { 2.3, 1.8, 3.2, 2.1, 0.7 } ;

    std::cout << wrap( names, ages ) << '\n' ;
}
