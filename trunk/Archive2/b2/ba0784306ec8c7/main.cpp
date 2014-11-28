#include <iostream>
#include <string>
#include <vector>

struct item
{
    std::string StockID ;
    std::string Type ;
    std::string Make ;
    std::string Model ;
    // etc.

    bool is_attribute( const std::string& str ) const
    { return str == StockID || str == Type || str == Make || str == Model /* ... */ ; }

    bool has_all_attributes_in( const std::vector<std::string>& attrib_set ) const
    {
        for( const std::string& str : attrib_set ) if( !is_attribute(str) ) return false ;
        return true ;
    }

};

void search( const std::vector<item>& db, const std::vector<std::string>& attrib_set )
{
    for( const item& it : db ) if( it.has_all_attributes_in(attrib_set) )
        std::cout << it.StockID << ' ' << it.Type << ' ' << it.Make << ' ' << it.Model << '\n' ;
}

int main( int argc, char* argv[] )
{
    const std::vector<item> db
    {
        { "0001", "Laptop", "HP", "COMPAQ/2400T" },
        { "0002", "Laptop", "DELL", "INSPIRON/990" },
        { "0003", "Laptop", "Lenovo", "5431" },
        { "0002", "Desktop", "DELL", "whatever" },
        { "0002", "Laptop", "DELL", "some/other/model" },
        
        // ...
    } ;
    
    if( argc > 1 ) search( db, { argv+1, argv+argc } ) ;
}
