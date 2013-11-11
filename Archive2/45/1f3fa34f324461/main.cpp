#include <iostream>
#include <vector>

struct cat
{
    enum colour_t { TABBY, HARLEQUIN, TORTOISESHELL, MALTESE };

    cat( const std::string& name, colour_t clr ) : name(name), colour(clr) {}

    std::string name ;
    colour_t colour ;
};

int main()
{
    // create four cats
    std::vector<cat> felines { { "Felix", cat::HARLEQUIN }, { "Sonja", cat::MALTESE },
                               { "Lilian", cat::TORTOISESHELL }, { "Baron", cat::TABBY } };

    // create another cat
    felines.emplace_back( "Mina", cat::HARLEQUIN ) ;

    // one more
    felines.emplace_back( "Orion", cat::TORTOISESHELL ) ;


    // print out the names
    for( const cat& c : felines ) std::cout << c.name << '\n' ;
}
