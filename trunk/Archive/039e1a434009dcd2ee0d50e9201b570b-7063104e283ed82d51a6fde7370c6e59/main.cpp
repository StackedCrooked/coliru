#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
 
int main()
{
    std::vector<std::pair<int, int>> v = 
    { 
        std::pair<int, int>( 0, 13 ),
        std::pair<int, int>( 20, 25 ),
        std::pair<int, int>( 0, 13 ),
        std::pair<int, int>( 20, 25 ),
        std::pair<int, int>( 30, 30 ),
        std::pair<int, int>( 170, 179 )
    };
    
    for ( std::pair<int, int> p : v )
    {
        std::cout << '<' << p.first << ',' << p.second << ">\n";
    }
    std::cout << std::endl;
    
   
}
