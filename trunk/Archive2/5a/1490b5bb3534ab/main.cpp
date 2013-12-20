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

text insert( text txt, std::size_t row, std::size_t col, char c )
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

text erase( text txt, std::size_t row, std::size_t col )
{
    if( row < txt.size() )
    {
        auto& line = txt[row] ;
        if( col < line.size() ) line.erase(col) ;
    }

    return txt ;
}

text erase( text txt, std::size_t row )
{
    if( row < txt.size() ) txt.erase( txt.begin() + row ) ;
    return txt ;
}

text erase_newline( text txt, std::size_t row )
{
    if( row < txt.size()-1 )
    {
        txt[row] += txt[row+1] ;
        txt.erase( txt.begin() + row+1 ) ;
    }

    return txt ;
}

///////////////////   facade   ////////////////////////

struct Char
{
    explicit Char( char c ) : this_char(c) {}

    char this_char = 0 ;
    Char* left = nullptr ;
    Char* right = nullptr ;
    Char* up = nullptr ;
    Char* down = nullptr ;
};

using Char2d = std::vector< std::vector<Char> > ;

text make_text( const Char2d& c2d )
{
    text txt ;
    for( const auto& row : c2d )
    {
        std::string str ;
        str.reserve( row.size() ) ;
        for( const auto& node : row ) str += node.this_char ;
        txt.push_back( std::move(str) ) ;
    }
    return txt ;
}

Char2d make_2d( const text& txt )
{
    Char2d c2d ;

    for( const auto& line : txt )
    {
        std::vector<Char> v ;
        for( char c : line ) v.emplace_back(c) ;
        c2d.push_back( std::move(v) ) ;
    }

    for( std::size_t i = 0 ; i < c2d.size() ; ++i )
    {
        auto& row = c2d[i] ;
        const auto sz = row.size() ;
        for( std::size_t j = 0 ; j < sz ; ++j )
        {
            if( j != 0 ) row[j].left = std::addressof( row[j-1] ) ;
            if( j != sz-1 ) row[j].right = std::addressof( row[j+1] ) ;
            if( i > 0 && c2d[i-1].size() > j )
                row[j].up = std::addressof( c2d[i-1][j] ) ;
            if( i != c2d.size() - 1 && c2d[i-1].size() > j )
                row[j].down = std::addressof( c2d[i-1][j] ) ;
        }
    }

    return c2d ;
}

Char2d& insert( Char2d& c2d, std::size_t row, std::size_t col, char c )
{ return c2d = make_2d( insert( make_text(c2d), row, col, c ) ) ; }

Char2d& erase( Char2d& c2d, std::size_t row, std::size_t col )
{
    if( row < c2d.size() && col < c2d[row].size() )
        c2d = make_2d( erase( make_text(c2d), row, col ) ) ;
    return c2d ;
}

Char2d& erase( Char2d& c2d, std::size_t row )
{
    if( row < c2d.size() ) c2d = make_2d( erase( make_text(c2d), row ) ) ;
    return c2d ;
}

Char2d& erase_newline( Char2d& c2d, std::size_t row )
{
    if( row < c2d.size()-1 ) c2d = make_2d( erase_newline( make_text(c2d), row ) ) ;
    return c2d ;
}

std::ostream& operator<< ( std::ostream& stm, const Char2d& c2d )
{ return stm << make_text(c2d) ; }

int main()
{
    Char2d c2d = make_2d(
    {
        "Create a notepad that allows the user to",
        "write text on the console.",
        "For this purpose, the user should be able to",
        "control and track the movement of the cursor.",
        "The user can access, add and delete",
        "any part of the text.",

    } );

    std::cout << c2d << "--------------------------------\n" ;

    insert( c2d, 2, 27, '\n' ) ;
    std::cout << c2d << "--------------------------------\n" ;

    insert( c2d, 3, 27, '#' ) ;
    insert( c2d, 3, 28, '!' ) ;
    std::cout << c2d << "--------------------------------\n" ;
    insert( c2d, 9, 27, '#' ) ;
    insert( c2d, 9, 28, '!' ) ;
    std::cout << c2d << "--------------------------------\n" ;

    erase( c2d, 8 ) ;
    std::cout << c2d << "--------------------------------\n" ;

    erase( c2d, 7 ) ;
    erase( c2d, 7 ) ;
    erase( c2d, 3, 27 ) ;
    erase( c2d, 3, 27 ) ;
    erase_newline( c2d, 2 ) ;
    std::cout << c2d << "--------------------------------\n" ;
}
