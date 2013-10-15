#include <iostream>
#include <sstream>

void pretty_print( std::istream& stm, std::size_t col_width )
{
    if( col_width < 20 ) return ;

    std::string line ;
    std::string token ;

    while( stm >> token ) // for each ws delimited token
    {
        auto required = token.size() + 1 ;
        if( ( line.size() + required ) > col_width ) // the next token won't fit
        {
            std::cout << line << '\n' ; // print the line
            line.clear() ; // make it an empty line
        }
        if( !line.empty() ) line += ' ' ; // add a space to seperate the tokens
        line += token ;
    }
    if( !line.empty() ) std::cout << line << '\n' ; // print the last line
}

int main()
{
    std::istringstream stm { R"(
        The Gettysburg Address
        Fourscore and seven years ago
        our fathers brought forth on
        this continent a new nation,
        conceived in liberty, and dedicated to
        the proposition that all men are created equal.
        Now we are engaged in a great civil war, testing
        whether that
        nation, or any nation so conceived and so dedicated,

        can long endure.
        We are met on a great battlefield of that war.
        We have come to dedicate a portion of that field as a final resting-place for those
        who here gave their lives that the nation might live.
    )" } ;

    pretty_print( stm, 40 ) ;
}
