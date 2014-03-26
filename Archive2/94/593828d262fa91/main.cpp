#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <fstream>

bool ends_with( const std::string& word, const std::string& suffix )
{
    return word.size() > suffix.size() &&
            word.substr( word.size() - suffix.size() ) == suffix ;
}

// crude stemmer
// rules:
// if the word ends in 'ed', remove the 'ed'
// if the word ends in 'ing', remove the 'ing' // wing ???
// if the word ends in ''s', remove the ''s'
// add more rules as appropriate
std::string strip_suffix( const std::string& word )
{
    static const std::string suffixes[] = { "ed", "ing", "'s" } ;

    for( const std::string& s : suffixes ) if( ends_with( word, s ) )
        return word.substr( 0, word.size() - s.size() ) ;

    return word ;
}

// make all lower case
std::string to_lower( std::string word )
{
    for( char& c : word ) c = std::tolower(c) ;
    return word ;
}

// make all lower case, strip suffix, remove punctuation
std::string sanitize( std::string word )
{
    std::string result ;
    word = strip_suffix( to_lower(word) ) ;
    for( char c : word ) if( std::isalnum(c) ) result += c ;
    return result ;
}

int main()
{
    const std::string filepath = "C:\\Users\\Connor\\Desktop\\JARVIS\\";
	const std::string filename = "VoiceData1.txt";
	std::map< std::string, int > wc ;

	std::ifstream file( __FILE__ /*filepath + filename*/ ) ;
	std::string word ;
	while( file >> word )
    {
        const std::string key = sanitize(word) ;
        if( !key.empty() ) ++wc[key] ;
    }

	// std::cout << "frequency count:\n-----------\n" ;
	// for( const auto& p : wc ) std::cout << p.first << " - " << p.second << '\n' ;

    /*
	test cases:
	test Test tested testing
	case Case cases Case's
	Your Your's your your's
	walk Walking Walked
	sleep slept Sleeping sleeps
    */

    std::cout << "test - " << wc[ "test" ] << '\n'
              << "case - " << wc[ "case" ] << '\n'
              << "your - " << wc[ "your" ] << '\n'
              << "walk - " << wc[ "walk" ] << '\n'
              << "sleep - " << wc[ "sleep" ] << '\n'
              << "slept - " << wc[ "slept" ] << '\n'
              << "sleeps - " << wc[ "sleeps" ] << '\n' ;
}
