#include <iostream>
#include <set>
#include <utility>

int main()
{
    std::set< std::pair< std::string, std::string> > books  =
    {
        { "Charlie Wilson", "Gone Far" },
        { "James Wilson", "The Water" },
        { "Charlie Wilson", "Clocks Gone" },
        { "James Wilson", "Zebra" },
        { "James Wilson", "Aardvark" },
        { "Charlie Wilson", "Fargone Clocks" }
    };

    for( const auto& pair : books )
        std::cout << "author: '" << pair.first << "' book: '" << pair.second << "'\n" ;
}
