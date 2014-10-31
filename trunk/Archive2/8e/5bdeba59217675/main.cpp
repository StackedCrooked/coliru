#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <sstream>

using anagram_map = std::unordered_map< std::string, std::vector<std::string> > ;

std::string make_key( std::string letters )
{
    for( char& c : letters ) c = std::tolower(c) ;
    std::sort( letters.begin(), letters.end() ) ;
    return letters ;
}

anagram_map make_anagram_map( std::istream& stm )
{
    anagram_map result ;
    std::string word ;
    while( stm >> word ) result[ make_key(word) ].push_back(word) ;
    return result ;
}

std::vector<std::string> look_up( const std::string& letters, const anagram_map& amap )
{
    auto iter = amap.find( make_key(letters) ) ;
    return iter != amap.end() ? iter->second : std::vector<std::string>{} ;
}

int main()
{
    std::istringstream word_list( "leapt palet petal plate pleat keel leek blase sable "
                                  "sleep peels builder rebuild "
                                  "again it only works for small lists of words "
                                  "lets say your words are limited to " ) ;

    auto amap = make_anagram_map(word_list) ;

    std::string letters ;
    while( std::cin >> letters )
    {
        std::cout << "scrambled letters: '" << letters ;
        const auto anagrams = look_up( letters, amap )  ;
        if( anagrams.empty() ) std::cout << "' => no words were found\n" ;
        else
        {
            std::cout << "' => words: " ;
            for( const std::string& ana : anagrams ) std::cout << "'" << ana << "' " ;
            std::cout << '\n' ;
        }
    }
}
