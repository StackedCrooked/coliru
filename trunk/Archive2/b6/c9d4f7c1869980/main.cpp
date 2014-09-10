#include <iostream>
#include <map>
#include <string>
#include <cctype>

std::string trim( std::string str )
{
    std::string result ;
    for( char c : str ) if( !std::isspace(c) ) result += c ;
    return result ;
}

struct symbol_table // integers
{
    void define_symbol()
    {
        std::string name ;
        std::cout << "enter name of variable: " ;
        std::cin >> name ;
        name = trim(name) ;
        // validate name
        int value ;
        std::cout << "enter value of " << name << ": " ;
        std::cin >> value ;
        symbols[name] = value ;
    }

    int operator[] ( std::string name ) const
    {
        auto iter = symbols.find(name) ;
        return iter != symbols.end() ? iter->second : 0 ; // pearl-like
    }

    int& operator[] ( std::string name ) { return symbols[ trim(name) ] ; }

    std::map< std::string, int > symbols ;
};


int main()
{
    symbol_table sym_tab ;
    sym_tab.define_symbol() ;

    std::string equation ;
    std::cout << "equation? " ;
    std::cin >> equation ;

    // parser p ; p.parse(equation) ; etc. (write a parser class)

    // for exposition; just do something crude to evaluate the first symbol
    // for brevity, assume that equation starts with a symbol
    std::size_t pos = equation.find_first_of( "=+-*/ " ) ;
    std::string symbol = equation.substr( 0, pos ) ;
    symbol = trim(symbol) ;

    std::cout << "\n\nsymbol: '" << symbol << "'  value: " << sym_tab[symbol] << '\n' ;
}
