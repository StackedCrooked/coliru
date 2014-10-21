#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <utility>
#include <fstream>

// breaks it into a sequence of words
// (using any character other than a digit or an alphabetical symbol as the terminator
std::vector<std::string> words_in( std::string line )
{
    std::vector<std::string> result ;
    std::string word ;

    for( char c : line )
    {
        if( std::isalnum(c) ) word += c ; // http://en.cppreference.com/w/cpp/string/byte/isalnum

        else
        {
            if( !word.empty() )
            {
                result.push_back(word) ;
                word.clear() ;
            }
        }
    }
    return result ;
}

// std::pair< int, std::vector<std::string> > => pair( line number, words in that line )
// http://en.cppreference.com/w/cpp/utility/pair
std::vector< std::pair< int, std::vector<std::string> > > lines_and_words_in( std::string path_to_file )
{
    std::vector< std::pair< int, std::vector<std::string> > > result ;

    std::ifstream file(path_to_file) ;
    std::size_t line_number = 0 ;
    std::string line ;

    while( std::getline( file, line ) ) // http://en.cppreference.com/w/cpp/string/basic_string/getline
    {
        ++line_number ;
        const auto words = words_in(line) ;
        // http://en.cppreference.com/w/cpp/container/vector/emplace_back
        if( !words.empty() ) result.emplace_back( line_number, words ) ; // std::move(words)
    }

    return result ;
}

int main()
{
    for( const auto& pair : lines_and_words_in( __FILE__ ) )
    {
        std::cout << "line number " << pair.first << "\n\twords: " ;
        for( std::string word : pair.second ) std::cout << word << ' ' ;
        std::cout << "\n\n" ;
    }
}
