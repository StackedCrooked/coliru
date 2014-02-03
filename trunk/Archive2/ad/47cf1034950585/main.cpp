#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <map>
#include <fstream>

// define a class to hold the information
struct word_info
{
    enum part_of_speech_t { NOUN, PRONOUN,  ADJECTIVE, DETERMINANT,
                             VERB, ADVERB, PREPOSITION, CONJUNCTION, UNKNOWN };
    part_of_speech_t part_of_speech ;
    std::vector<std::string> synonyms ; // www.mochima.com/tutorials/vectors.html
    std::string definition ;
};

constexpr char TAB = '\t' ; // http://www.stroustrup.com/C++11FAQ.html#constexpr
constexpr char SPACE = ' ' ;
constexpr char NEWLINE = '\n' ;

// provide a function to write the information into a stream
std::ostream& operator<< ( std::ostream& stm, const word_info& info )
{
    // wrie part_of_speech, TAB
    stm << info.part_of_speech << TAB ;

    // write synonyms, TAB
    // http://www.stroustrup.com/C++11FAQ.html#for
    for( const std::string& synonym : info.synonyms ) stm << synonym << SPACE ;
    stm << TAB ;

    // write definition, NEWLINE
    return stm << info.definition << NEWLINE ;
}

// provide a function to read the information from a stream
std::istream& operator>> ( std::istream& stm, word_info& info )
{
    // read part_of_speech
    int pos ;
    stm >> pos ;
    if( pos >= word_info::NOUN && pos < word_info::UNKNOWN )
        info.part_of_speech = word_info::part_of_speech_t(pos) ;
    else info.part_of_speech = word_info::UNKNOWN ;

    // http://www.cplusplus.com/reference/istream/istream/ignore/
    stm.ignore( 1000, TAB ) ; // throw away the TAB after part of speech

    // read synonyms, upto the next TAB
    std::string synonyms ;

    // http://www.cplusplus.com/reference/string/string/getline/
    std::getline( stm, synonyms, TAB ) ;

    // http://www.cplusplus.com/reference/sstream/istringstream/
    std::istringstream str_stream(synonyms) ;

    // http://www.cplusplus.com/reference/iterator/istream_iterator/
    std::istream_iterator<std::string> begin(str_stream), end ;

    // http://www.stroustrup.com/C++11FAQ.html#uniform-init
    info.synonyms = { begin, end } ;

    // read definition, everything left up to the NEWLINE
    return std::getline( stm, info.definition, NEWLINE ) ;
}

// defie a dictionary type to associate a word with its word_info
// http://www.cplusplus.com/reference/map/map/
// http://www.stroustrup.com/C++11FAQ.html#template-alias
using dictionary_type = std::map< std::string, word_info > ;

// provide a function to look up the dictionar for synonyms
std::vector<std::string> synonyms( const std::string& word, const dictionary_type& dict )
{
   auto iter = dict.find(word) ;
   return iter != dict.end() ? iter->second.synonyms : std::vector<std::string>{} ;
}

// TODO: provide a function to look up the dictionar for part_of_speech
word_info::part_of_speech_t pos( const std::string& word, const dictionary_type& dict ) ;

// TODO: provide a function to look up the dictionar for definition
std::string definition( const std::string& word, const dictionary_type& dict ) ;


// now, put it all together
int main()
{
    // create a dictionary mapping word toword_info
    dictionary_type dictionary // http://www.stroustrup.com/C++11FAQ.html#uniform-init
    {
        {
            "synonym",
            {
                word_info::NOUN,
                { "metonym", "equivalent", "analogue" },
                "word having or nearly the same meaning as another"
            }
        },
        {
            "colourful",
            {
                word_info::ADJECTIVE,
                { "hued", "vivid", "florid", "prismatic" },
                "richly or strikingly coloured"
            }
        },
        {
            "disembark",
            {
                word_info::VERB,
                { "alight", "dismount" },
                "get off a car, train, plane, ship etc."
            }
        }
        // etc.
    };

    // write the contents to a file
    const char* const file_name = "dict.txt" ;
    {
        std::ofstream file(file_name) ;
        for( const auto& pair : dictionary )
            file << pair.first << TAB << pair.second << NEWLINE ;
    }

    dictionary.clear() ; // empty the dictionary

    // read the contents back from the file
    {
        std::ifstream file(file_name) ;
        std::string word ;
        word_info info ;
        while( std::getline( file >> std::ws, word, TAB ) && file >> info )
            dictionary.emplace( word, info ) ;
    }

    // add two americanglish synonyms for disembark
    const std::string disembark = "disembark" ;
    dictionary[disembark].synonyms.push_back( "deplane" ) ;
    dictionary[disembark].synonyms.push_back( "detrain" ) ;

    // lookup and print synonyms for "disembark"
    std::cout << "synonyms for " << disembark << ": " ;
    for( const std::string& synonym : synonyms( disembark, dictionary ) )
        std::cout << synonym << SPACE ;
    std::cout << NEWLINE ;
}
