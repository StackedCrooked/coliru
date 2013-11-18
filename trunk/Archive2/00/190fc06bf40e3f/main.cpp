#include <iostream>
#include <string>
#include <sstream>

// return true if in str, substring a appears before substring b
bool before( const std::string& str, const std::string& a, const std::string& b )
{
    const std::size_t apos = str.find(a) ;
    const std::size_t bpos = str.find(b) ;

    static const std::size_t npos = std::string::npos ;
    return apos != npos && bpos != npos && apos < bpos ;
}

// return true if in str, word a appears before word b
// where a word is defined as a white-space delimited substring
bool word_before( const std::string& str, const std::string& a, const std::string& b )
{
    std::istringstream stm(str) ;
    std::string word ;
    while( stm >> word && word != a ) ;
    while( stm >> word && word != b ) ;
    return stm.good() ;
}

int main()
{
    const std::string& str = "how now brown cow" ;
    std::cout << std::boolalpha
               << before( str, "now", "cow" ) << '\n' // true
               << before( str, "now", "wow" ) << '\n' // false
               << before( str, "bow", "cow" ) << '\n' // false
               << before( str, "how now", " brow" ) << '\n' ; // true

    std::cout << "-------\n"
               << word_before( str, "now", "cow" ) << '\n' // true
               << word_before( str, "now", "wow" ) << '\n' // false
               << word_before( str, "ho", "cow" ) << '\n' // false
               << word_before( str, "how", "brow" ) << '\n' ; // false
}
