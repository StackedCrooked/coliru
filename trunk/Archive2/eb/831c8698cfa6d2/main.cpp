#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int main()
{
    {
        // create infile for tesing
        std::ofstream( "Names.txt" ) << "Miller, Jason Brian\n"
                                        "Blair, Lisa Maria\n"
                                        "Gupta, Anil Kumar\n"
                                        "Arora, Sumit Sahil\n"
                                        "Saleh, Rhonda Beth\n" ;
    }

    std::ifstream infile( "Names.txt" ); // open the input file
    std::ofstream outfile( "NamesRevised.txt" ) ; // and the output file

    std::string line ;
    while( std::getline( infile, line ) ) // canonical: for each line in the input file
    {
        std::istringstream stm(line) ; // initialise a string stream than reads from the line

        std::string last_name ;
        std::getline( stm, last_name, ',' ) ; // read everything up to the comma, extract and discard the comma

        std::string first_name, middle_name ;
        stm >> first_name >> middle_name ; // skips leading white space

        char initial = middle_name.empty() ? ' ' : middle_name[0] ;

        std::cout << first_name << ' ' << initial << ' ' << last_name << '\n';
        outfile << first_name << ' ' << initial << ' ' << last_name << '\n';
    }
}
