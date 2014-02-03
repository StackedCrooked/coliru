#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <iterator>
#include <algorithm>

std::vector<std::string> tokenize( const std::string& str )
{
    std::vector<std::string> tokens ;
    static const auto ws = [] ( char c ) { return std::isspace(c) != 0 ; } ;

    auto iter = std::begin(str) ;
    static const auto next = [&]
    {
        return ws(*iter) ? std::find_if_not( iter+1, std::end(str), ws ) :
                            std::find_if( iter+1, std::end(str), ws ) ;
    };

    while( iter != std::end(str) )
    {
        auto nxt = next() ;
        tokens.emplace_back( iter, nxt ) ;
        iter = nxt ;
    }

    return tokens ;
}

void print_reverse( const std::string& str )
{
    const auto tokens = tokenize(str) ;
    for( auto iter = tokens.rbegin() ; iter != tokens.rend() ; ++iter )
        std::cout << *iter ;
    std::cout << '\n' ;
}

int main()
{
    const std::string str =
R"#(1.    Tomorrow, and tomorrow, and tomorrow,
2.    Creeps in this petty pace from day to day,
3.    To the last syllable of recorded time;
4.    And all our yesterdays have lighted fools
5.    The way to dusty death. Out, out, brief candle!
6.    Life's but a walking shadow, a poor player
7.    That struts and frets his hour upon the stage
8.    And then is heard no more. It is a tale
9.    Told by an idiot, full of sound and fury
10.   Signifying nothing.
**************************************************
***********     William Shakespeare    ***********
***********          (Macbeth)         ***********
**************************************************)#" ;

    std::cout << str << "\n\n" ;
    print_reverse(str) ;
}
