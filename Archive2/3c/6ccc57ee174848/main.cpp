#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

int main ()
{
    // the line read from the file
    std::string line = "5/15 200 Deposit cash NULL 14454.23" ;

    // split it into white-space separated tokens
    std::vector<std::string> tokens ; // #include <vector>
    {
        // create an input string stream
        std::istringstream stm(line) ; // #include <sstream>

        std::string tok ;
        // extract token by token and add to vector
        while( stm >> tok ) tokens.push_back(tok) ;
    }

    // print out the tokens
    for( const std::string& tok : tokens ) std::cout << tok << '\n' ;

    if( tokens.size() > 4 )
    {
        // convert the second and last tokens to double
        double amount = std::stod( tokens[1] ) ;
        double balance = std::stod( tokens.back() ) ;

        // update the balance
        if( tokens[2] == "Deposit" ) balance += amount ;
        else balance -= amount ;

        std::cout << "\nupdated balance: " << std::fixed << std::setprecision(2) << balance << '\n' ;
    }
}
