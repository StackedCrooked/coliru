#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

int main()
{
    std::string linea = "How now BROWN cow." ;
    std::string palabraBuscar = "brown" ;

    // case insentive search
    auto result = std::search( linea.begin(), linea.end(), // search in this sequence of characters

                                palabraBuscar.begin(), palabraBuscar.end(), // for this subsequence

                                [] ( char a, char b ) { return std::toupper(a) == std::toupper(b) ; }
                                // ignoring case while comparing characters for equality
                               ) ;

    if( result != linea.end() ) // if the susequence was found
    {
        std::cout << "found: '" << palabraBuscar << "' starting at position " << result - linea.begin()
                  << " in line: '" << linea << "'\n" ;
    }
}
