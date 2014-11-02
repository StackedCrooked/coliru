#include <iostream>
#include <string>
#include <map>
#include <sstream>

// maps symbol to pair number, name eg. "As" => {5,"Arsenic"}
using lookup_table = std::map< std::string, std::pair<int,std::string> > ;

lookup_table make_lookup_table( std::istream& stm )
{
    lookup_table table ;

    std::string name, symbol ;
    int value ;
    while( stm >> name >> symbol >> value ) table[symbol] = { value, name } ;

    return table ;
}

std::ostream& save_lookup_table( const lookup_table& table, std::ostream& stm )
{
    for( const auto& pair : table )
        stm << pair.second.second << ' ' << pair.first << ' ' <<  pair.second.first << '\n' ;
    return stm ;
}

int main()
{
    std::istringstream file( R"(
                                   Arsenic As 5
                                   Helium He 2
                                   Zinc Zn 30
                                   Krypton Kr 1
                               )" ) ;
    const lookup_table table = make_lookup_table(file) ;

    std::string key ;
    while( std::cin >> key )
    {
        auto iter = table.find(key) ;
        if( iter != table.end() )
            std::cout << key << " => value: " << iter->second.first << " name: " << iter->second.second << '\n' ;
        else std::cerr << "*** error *** symbol '" << key << "' was not found\n" ;
    }
}
