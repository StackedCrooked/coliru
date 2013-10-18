#include <iostream>
#include <vector>

void remove_negatives( std::vector<int>& seq )
{
    if( !seq.empty() )
    {
        const int v = seq.back() ;
        seq.pop_back() ;

        remove_negatives(seq) ;

        if( v >= 0 ) seq.push_back(v) ;
    }
}

int main()
{
    std::vector<int> seq { -34, -21, 5, 72, -2, 17 } ;
    remove_negatives(seq) ;

    for( int v : seq ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}
