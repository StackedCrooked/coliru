#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

struct node
{
    std::vector<int> keys ;
    std::vector<int> children ;
};

const std::string lead_in = "keys: " ;
const std::string seperator = " child_indices: " ;

std::ostream& operator<< ( std::ostream& stm, const node& n )
{
    stm << lead_in ;
    for( int key : n.keys ) stm << key << ' ' ;
    stm << seperator ;
    for( int child : n.children ) stm << child << ' ' ;
    return stm << '\n' ;
}

std::istream& operator>> ( std::istream& stm, node& n )
{
    n = node() ;

    std::string line ;
    std::getline( stm, line ) ;

    std::istringstream strstm(line) ;
    std::string lead ;
    strstm >> lead ; // extract the seperator
    // verify that lead == lead_in
    
    int v ;
    while( strstm >> v ) n.keys.push_back(v) ;

    strstm.clear() ;
    std::string sep ;
    strstm >> sep ; // extract the seperator
    // verify that sep == seperator

    while( strstm >> v ) n.children.push_back(v) ;

    return stm ;
}

int main()
{
    const std::vector<node> b_tree =
    {
        { { 1234, 5678 }, { 1, 2 } },          // #0
        { { 2345, 8321, 4578 }, { 3 } },       // #1
        { { 1000, 8765 }, { 4, 5, 6 } },       // #2
        { { 2134, 6789, 1238, 5555 }, { 7 } }, // #3
        { { 8855 }, {} },                      // #4
        { { 9927, 5610 }, {} },                // #5
        { { 1617, 5821, 5000 }, {} },          // #6
        { { 7299 }, {} }                       // #7
    };

    std::stringstream file ;
    for( const node& n : b_tree ) file << n ;

    std::cout << "file contains:\n" << file.str() ;

    file.seekg(0) ;
    std::vector<node> cpy ;
    node n ;
    while( file >> n ) cpy.push_back(n) ;

    static const auto eq = [] ( const node& a, const node& b )
    { return a.keys == b.keys && a.children == b.children ; } ;

    std::cout << "**** b_tree equal to cpy? " << std::boolalpha
              << std::equal( b_tree.begin(), b_tree.end(), cpy.begin(), eq ) << '\n' ;
}
