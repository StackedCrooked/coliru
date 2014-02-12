#include <iostream>
#include <string>
#include <map>

struct aClass { std::string a, b ; double d ; };

int main()
{
    std::map< std::string, std::map< std::string, aClass > > myMap = 
    {
        {
            "abc",
            {
                { "defg", { "one", "two", 1.2 } },
                { "hijk", { "three", "four", 3.4 } },
                { "lmno", { "five", "six", 5.6 } }
            }
        },
        
        {
            "pqr",
            {
                { "stuv", { "seven", "eight", 7.8 } },
                { "wxyz", { "nine", "zero", 9.0 } }
            }
        }
    };
    
    // iterate using range-based loop
    {
        for( const auto& sm_pair : myMap )
        {
            std::cout << sm_pair.first << '\n' ;
            for( const auto& sc_pair : sm_pair.second )
            {
                std::cout << "     " << sc_pair.first << '{' << sc_pair.second.a << ',' 
                          << sc_pair.second.b << ',' << sc_pair.second.d << "}\n" ;    
            }
        }
    }
    
    std::cout << "----------------------\n" ;
    
    // iterate C++98 style
    {
        typedef std::map< std::string, std::map< std::string, aClass > >::iterator outer_iterator ;
        typedef std::map< std::string, aClass >::iterator inner_iterator ;
        
        for( outer_iterator outer = myMap.begin() ; outer != myMap.end() ; ++outer )
        {
            std::cout << outer->first << '\n' ;
            for( inner_iterator inner = outer->second.begin() ; inner != outer->second.end() ; ++inner )
            {
                std::cout << "     " << inner->first << '{' << inner->second.a << ',' 
                          << inner->second.b << ',' << inner->second.d << "}\n" ;    
            }
        }
    }
}

