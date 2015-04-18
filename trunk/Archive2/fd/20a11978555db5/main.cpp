#include <forward_list>
#include <iostream>

int main()
{
    std::forward_list < int > foo { 1, 2, 3, 4, 5 };
    
    for ( int i : foo )
    {
        if ( i == 1 ) foo.push_front ( 0 );
        
        std::cout << i << std::endl;
    }
    
    return EXIT_SUCCESS;
}
