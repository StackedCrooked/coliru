#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec { 0, 1, 2, 3, 4, 5 } ;
    vec.reserve( vec.size() * 2 ) ; // optional

    auto n = vec.size() ; // size before the inserts

    // insert 99 at every alternate position (insert 99 n times)
    for( auto iter = std::begin(vec) ; n-- ; ++iter )
        iter = vec.insert( iter+1, 99 ) ; // vec.insert() returns a valid iterator
                                           // to the element that was inserted

    for( int v : vec ) std::cout << v << ' ' ;
    std::cout << '\n' ;
}
