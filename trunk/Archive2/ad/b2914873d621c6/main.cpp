#include <string>
#include <vector>
#include <cctype>
#include <sstream>
#include <iostream>

// replace punctuation with space, convert to lower case
std::string sanitize( const std::string& str )
{
    std::string result ;
    for( char c : str )
    {
        if( std::ispunct(c) ) result += ' ' ;
        else result += std::tolower(c) ;
    }
    return result ;
}

// remove leading and trailing whitespace
std::string trim( std::string str )
{
    std::stringstream stm ;
    stm << str ;
    stm >> str ;
    return str ;
}

bool sentence_has_word( std::string sentence, std::string word )
{
    sentence = sanitize(sentence) ;

    word = trim( sanitize(word) ) ;
    if( word.size() > sentence.size() ) return false ;
    if( word.size() == sentence.size() ) return word == sentence ;

    auto pos = sentence.find( word + ' ' ) ; // check for word at the beginning
    if( pos == 0 ) return true ;
    
    pos = sentence.find( ' ' + word + ' ' ) ; // check for word in the middle
    if( pos != std::string::npos ) return true ; 
    
    word = ' ' + word ;
    return sentence.substr( sentence.size() - word.size() ) == word  ; // check for word at the end
}

int main()
{
    const std::vector<std::string> sentences =
    {
        "The woods are lovely, dark, and deep, "
        "But I have promises to keep, "
        "And miles to go before I sleep.",

        "You linger your little hour and are gone, "
        "And still the woods sweep leafily on.",

        "Two roads diverged in a wood, and I, "
        "I took the one less traveled by, "
        "And that has made all the difference."
    };

    const std::vector<std::string> words =
    { "wood", "Woods", "DARK", "be", "fore", " traveled ", " linger ", "two" };

    for( std::string word : words )
    {
        std::cout << '"' << word << "\"\n" ;
        for( std::string sentence : sentences )
            if( sentence_has_word(sentence,word) ) std::cout << sentence << '\n' ;
        std::cout << '\n' ;
    }
}
