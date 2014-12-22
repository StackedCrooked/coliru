#include <iostream>
#include <vector>

std::vector< std::vector<int> > split( const std::vector<int>& seq, int delta )
{
    if( delta < 0 ) delta = -delta ;
    std::vector< std::vector<int> >  result ;

     std::vector<int> curr ;
     for( int v : seq )
     {
        if( !curr.empty() && std::abs( v - curr.back() ) >= delta )
        {
            result.push_back(curr) ;
            curr.clear() ;
        }
        
        curr.push_back(v) ;
     }
     
     if( !curr.empty() ) result.push_back(curr) ;
     return result ;
}

void test_it( const std::vector<int>& seq, int delta )
{
    std::cout << "delta == " << delta << ": " ;
    const auto sub_vectors = split( seq, delta ) ;
    
    for( const auto& vec : sub_vectors )
    {
        std::cout << "{ " ;
        for( int v : vec ) std::cout << v << ' ' ;
        std::cout << "}  " ;
    }
    std::cout << "\n\n" ;
}

int main()
{
     const std::vector<int> my_vec = { 100, 103, 109, 110, 130, 138, 140, 144 } ;

     test_it( my_vec, 10 ) ;
     test_it( my_vec, 5 ) ;
     test_it( my_vec, 7 ) ;
}
