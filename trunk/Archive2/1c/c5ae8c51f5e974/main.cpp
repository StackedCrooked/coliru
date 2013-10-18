#include <iostream>
#include <vector>

int main()
{
    std::vector<int> seq { -34, -21, 5, 72, -2, 17 } ;
    std::vector<int> temp ;

    for( int v : seq ) if( v >= 0 ) temp.push_back(v) ;

    while( !seq.empty() ) seq.pop_back() ; // seq.clear()

    for( int v : temp ) seq.push_back(v) ;

    for( int v : seq ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}
