#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <initializer_list>

const std::vector<std::string> order_of_field_mames { "seven", "two", "five", "one", "four", "six", "three" } ;

struct compare_field_mames
{
    bool operator() ( const std::string& a, const std::string& b ) const
    {
        const auto iter_a = std::find( std::begin(order_of_field_mames), std::end(order_of_field_mames), a ) ;
        const auto iter_b = std::find( std::begin(order_of_field_mames), std::end(order_of_field_mames), b ) ;
        if( iter_a != std::end(order_of_field_mames) || iter_b != std::end(order_of_field_mames) ) // at least one was found
            return iter_a < iter_b ;
        else return a < b ; // nether a nor b was found in the vector
    }
};

struct storage_class
{
    void assign( const std::string& name, int value ) { name_value_pairs[name] = value ; }
    void assign( std::initializer_list< std::pair<std::string,int> > nv_pairs )
    { for( const auto& pair : nv_pairs ) assign( pair.first, pair.second ) ; }

    std::map< std::string, int, compare_field_mames > name_value_pairs ;

    std::ostream& write_lines( std::ostream& stm )
    {
        constexpr char DELIMITER = ';' ;
        for( const auto& pair : name_value_pairs ) stm << pair.first << DELIMITER ;
        stm << '\n' ;
        for( const auto& pair : name_value_pairs ) stm << pair.second << DELIMITER ;
        return stm << '\n' ;
    }
};

int main()
{
    storage_class sc ;
    sc.assign( { { "five", 5 }, { "nine", 9 }, { "four", 4 }, { "zero", 0 }, { "six", 6 }, { "two", 2 } } ) ;
    sc.write_lines(std::cout) ;
}
