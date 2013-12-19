#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using text = std::vector<std::string> ;

std::ostream& operator<< ( std::ostream& stm, const text& txt )
{
    int n = 0 ;
    for( const auto& line : txt )
        stm << std::setw(3) << n++ << ". " << line << '\n' ;
    return stm ;
}

text& insert( text& txt, std::size_t row, std::size_t col, char c )
{
    if( row >= txt.size() ) txt.resize(row+1) ;
    auto& line = txt[row] ;

    if( col > line.size() ) line.resize( col+1, ' ' ) ;

    if( c == '\n' )
    {
        auto tail = line.substr(col) ;
        line.resize(col) ;
        txt.insert( txt.begin() + row+1, tail ) ;
    }
    else line.insert( col, 1, c ) ;

    return txt ;
}

text& erase( text& txt, std::size_t row, std::size_t col )
{
    if( row < txt.size() )
    {
        auto& line = txt[row] ;
        if( col < line.size() ) line.erase(col) ;
    }

    return txt ;
}

text& erase( text& txt, std::size_t row )
{
    if( row < txt.size() ) txt.erase( txt.begin() + row ) ;
    return txt ;
}

text& erase_newline( text& txt, std::size_t row )
{
    if( row < txt.size()-1 )
    {
        txt[row] += txt[row+1] ;
        txt.erase( txt.begin() + row+1 ) ;
    }

    return txt ;
}

int main()
{
    text txt =
    {
        "Create a notepad that allows the user to",
        "write text on the console.",
        "For this purpose, the user should be able to",
        "control and track the movement of the cursor.",
        "The user can access, add and delete",
        "any part of the text.",

    };

    std::cout << txt << "--------------------------------\n" ;

    insert( txt, 2, 27, '\n' ) ;
    std::cout << txt << "--------------------------------\n" ;

    insert( txt, 3, 27, '#' ) ;
    insert( txt, 3, 28, '!' ) ;
    std::cout << txt << "--------------------------------\n" ;
    insert( txt, 9, 27, '#' ) ;
    insert( txt, 9, 28, '!' ) ;
    std::cout << txt << "--------------------------------\n" ;

    erase( txt, 8 ) ;
    std::cout << txt << "--------------------------------\n" ;

    erase( txt, 7 ) ;
    erase( txt, 7 ) ;
    erase( txt, 3, 27 ) ;
    erase( txt, 3, 27 ) ;
    erase_newline( txt, 2 ) ;
    std::cout << txt << "--------------------------------\n" ;
}
