#include <iostream>
#include <set>
#include <map>
#include <utility>

int main()
{
    std::multimap< std::string, std::string > authors =
    {
        { "Charlie Wilson", "Gone Far" },
        { "James Wilson", "The Water" },
        { "Charlie Wilson", "Clocks Gone" },
        { "James Wilson", "Zebra" },
        { "James Wilson", "Aardvark" },
        { "Charlie Wilson", "Fargone Clocks" }
    };

    std::set< std::pair< std::string, std::string > > books( authors.begin(), authors.end() ) ;
    for( const auto& pair : books )
        std::cout << "author: '" << pair.first << "' book: '" << pair.second << "'\n" ;
}
