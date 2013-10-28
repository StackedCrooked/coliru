#include <iostream>
#include <string>
#include <sstream>

int main()
{
    // http://www.mochima.com/tutorials/strings.html
    const std::string met = "MET" ;
    const std::string stop = "STO" ;
    constexpr char seperator = '-' ;

    const char array[] = "ILE-ASN-ASP-ARG-LYS-ASN-STO-MET-LYS-SER-ASP-LYS-STO-"
                           "ARG-GLN-ASP-SER-LYS-GLY-SER-MET-STO-RP-GLU-HIS-ALA-"
                           "MET-SER-LYS-GLY-SER-ASP-ARG-LYS-STO-MET-LYS-SER-ASP" ;

    // http://www.artima.com/cppsource/streamstrings3.html
    std::istringstream stm(array) ;

    std::string protein ;
    std::string codon ;

    // http://www.cplusplus.com/reference/string/string/getline/
    while( std::getline( stm, codon, seperator) )
    {
        if( codon == met ) protein = met ; // start new protein

        // http://www.cplusplus.com/reference/string/string/find/
        else if( protein.find(met) == 0 ) // if protein starts with "MET"
        {
            if( codon == stop )
            {
               if( protein.size() > met.size() ) // if there is a codon after "MET"
                   std::cout << protein + seperator + stop << '\n' ; // print it
               protein = "" ; // "STO", that is the end of this protein
            }
            else protein += seperator + codon ; // append the codon to the protein
        }
    }
}
