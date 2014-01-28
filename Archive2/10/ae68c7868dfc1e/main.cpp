#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <cctype>
#include <map>
#include <vector>

std::string& tolower( std::string& str )
{
    for( char& c : str ) c = std::tolower(c) ;
    return str ;
}

std::string trim_punct( std::string str )
{
    while( !str.empty() && std::ispunct( str.back() ) ) str.pop_back() ;
    return str ;
}

bool not_in_dictionary( const std::string& word, const std::set<std::string>& dict )
{ return dict.find(word) == dict.end() ; }

int main()
{
    std::set<std::string> dict ;

    // initalize dictionary
    {
        std::istringstream dict_stm( "if is in of be bugs the then them must" ) ;
        std::string word ;
        while( dict_stm >> word ) dict.insert( tolower(word) ) ;
    }

    std::map< std::string, std::vector<int> > misspelt ;

    // read file
    {
        std::istringstream doc_stm
        (
            "If debugging is the\n"
            "process of removing bugs.\n"
            "Then programming must be the\n"
            "process of putting them in.\n"
            "for testing: puTTing process, debugging++ reMOVing programmING.\n"
        );

        int line_number = 1 ;
        std::string line ;
        while( std::getline( doc_stm, line ) )
        {
            std::istringstream stm(line) ;
            std::string word ;
            while( stm >> word )
            {
                word = trim_punct( tolower(word) ) ;
                if( not_in_dictionary(word,dict) ) misspelt[word].push_back(line_number) ;
                ++line_number ;
            }
        }
    }

    // print misspelt
    for( const auto& pair : misspelt )
    {
        std::cout << pair.first << " [ " ;
        for( int n : pair.second ) std::cout << n << ' ' ;
        std::cout << "]\n" ;
    }
}
