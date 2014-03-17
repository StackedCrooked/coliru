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
        seq.push_back( std::make_pair(number,text) ) ; // add the pair to vector
        // http://en.cppreference.com/w/cpp/utility/pair/make_pair
        // http://en.cppreference.com/w/cpp/container/vector/push_back

    std::sort( seq.begin(), seq.end() ) ; // sort the pairs
    // http://en.cppreference.com/w/cpp/utility/pair/operator_cmp

    // and print out the sorted pairs
    // seq[i].first is the number, seq[i].second is the text
    for( std::size_t i = 0 ; i < seq.size() ; ++i )
        std::cout << seq[i].first << ' ' << seq[i].second << '\n' ;
}
