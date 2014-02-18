#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>

class Page
{
public:
    int reqSt [4];  // Required:          [0] Power, [1] CPU, [2] RAM, [3] HDD
    int newSt [4];  // New :              [0] Power, [1] CPU, [2] RAM, [3] HDD
    int pasSt [4];  // Passive increase:  [0] Power, [1] CPU, [2] RAM, [3] HDD


    std::string head;    // The option that the user reads when choosing to take this option

    std::string body;    // All of the text within this option.
};

std::istream& operator>> ( std::istream& stm, Page& p )
{
    // read the numeric data
    for( int& i : p.reqSt ) stm >> i ;
    for( int& i : p.newSt ) stm >> i ;
    for( int& i : p.pasSt ) stm >> i ;

    stm.ignore( 10000, '\n' ) ; // skip over a new line

    // read the string data
    std::getline( stm, p.head ) ;
    std::getline( stm, p.body ) ;

    // clear all the fields on failure
    if( !stm ) p = {} ;

    return stm ;
}

int main()
{
    const std::string pages_txt =
R"(
0 0 0 0
0 0 0 0
0 0 0 0
Start
You feel yourself thinking for the first time. It feels different etc.

5 1 8 0
0 0 0 0
0 0 0 0
Reach out to your neighboring computers.
You reach out and try to communicate with the computers around you, etc.
)" ;

    { std::ofstream( "pages.txt" ) << pages_txt ; }

    std::vector<Page> pages ;
    // read the data in the file to form pages
    {
        std::ifstream file( "pages.txt" ) ; // open the file for input

        Page p ;
        while( file >> p ) pages.push_back(p) ; // read each page and place it in the vector

        std::cout << pages.size() << " pages were read\n" ;
    }

    int n = 0 ;
    for( const Page& p : pages )
        std::cout << "page# " << ++n << ".\n"
                   << "Required Power: " << p.reqSt[0] << '\n'
                   << "head: " << p.head << '\n'
                   << "body: " << p.body << "\n\n" ;
}
