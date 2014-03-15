#include <iostream>
#include <vector>
#include <string>
#include <utility> // std::pair
#include <sstream> // #include <fstream>
#include <algorithm>
#include <iterator> // std::begin(), std::end()

int main()
{
    std::istringstream file // std::ifstream file("who.txt");
    ( "10 Tennant\n" "9 Eccleston\n" "12 Capaldi\n" "11 Smith\n" );

    // vector holding pairs int+string
    // http://en.cppreference.com/w/cpp/utility/pair
    std::vector< std::pair<int,std::string> > seq ;

    int number ;
    std::string text ;

    // for each line in the file
    while( file >> number && std::getline(file,text) ) // read the number and the string
        seq.emplace_back(number,text) ; // add the pair to vector
        // http://en.cppreference.com/w/cpp/container/vector/emplace_back

    std::sort( std::begin(seq), std::end(seq) ) ; // sort the pairs
    // http://en.cppreference.com/w/cpp/utility/pair/operator_cmp
    // http://en.cppreference.com/w/cpp/iterator/begin

    // and print out the sorted pairs
    // pair.first is the number, pair.second is the text
    for( auto pair : seq ) std::cout << pair.first << ' ' << pair.second << '\n' ;
}
