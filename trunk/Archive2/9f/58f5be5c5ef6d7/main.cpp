#include <forward_list>
#include <iostream>
#include <algorithm>

int main()
{
    std::forward_list<int> lst ; // create an empty list

    lst.push_front(12) ; // insert 12 at the front
    lst.push_front(10) ; // insert 10 at the front
    lst.push_front(8) ;

    lst.insert_after( lst.begin(), 9 ) ; // insert 9 after 8

    // insert 11 after 10
    lst.insert_after( std::find( lst.begin(), lst.end(), 10 ), 11 ) ;

    // print the list
    for( int v : lst ) std::cout << v << ' ' ; // 8 9 10 11 12
    std::cout << '\n' ;
}
