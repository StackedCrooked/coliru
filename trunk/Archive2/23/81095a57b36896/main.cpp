#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <tuple>

using namespace std;

int main(void) 
{
    std::vector< std::tuple< string, int, float, char > > elements;
    elements.push_back( std::make_tuple( "Hugo", 33, 44.1, 'x' ) );
    
    return 0;
}
