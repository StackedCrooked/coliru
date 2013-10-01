#include <iostream>
#include <string>
#include <vector>
#include <sstream>

int main()
{
    const std::string space( 1, ' ' ) ;
    const std::string three_spaces = space + space + space ;
    std::string str = "I ' m   s o r 0 y 4 D a v e , 5 12 12 12 3 ." ;

    // locate three consecutive spaces in the array
    auto pos = str.find(three_spaces) ;
    if( pos != std::string::npos ) // if found
    {
        // the part before three consecutive spaces
        std::string part_one = str.substr( 0, pos ) ;

        // the part after three consecutive spaces
        std::string part_two = str.substr( pos + three_spaces.size() ) ;

        // string with the middle space of the three consecutive spaces
        // replaced with a nullchar
        constexpr char nullchar = 0 ;
        str = part_one + space + nullchar + space + part_two ;

        // parse this string as in the earlier code
        std::vector<std::string> array ;
        std::istringstream stm(str) ;
        std::string temp ;
        while( stm >> temp )
        {
            // except that if it is a nullchar, replace it with a space
            if( temp.front() == nullchar ) array.push_back(space) ;
            else array.push_back(temp) ;
        }

        // dump the contents of the array to check it out
        int n = 0 ;
        for( const std::string& token : array )
            std::cout << ++n << ". \"" << token << "\"\n" ;
    }
}
