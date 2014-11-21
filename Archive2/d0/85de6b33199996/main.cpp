#include <iostream>
#include <set>
#include <map>
#include <utility>

int main()
{
    std::map< std::string, std::set<std::string> > authors =
    {
        { "Charlie Wilson", { "Gone Far", "Clocks Gone", "Fargone Clocks" } },
        { "James Wilson", { "The Water", "Zebra", "Aardvark" } }
    };

    authors[ "Charlie Wilson" ].insert( "Clocks Gone Far" ) ;
    authors[ "JLBorges" ].insert( ""The Garden of Forking Paths" ) ;

    for( const auto& pair : authors )
    {
        std::cout << "\nauthor: '" << pair.first << "'\n" ;
        for( const auto& str : pair.second ) std::cout << "\tbook: '" << str << "'\n" ;
    }
}
