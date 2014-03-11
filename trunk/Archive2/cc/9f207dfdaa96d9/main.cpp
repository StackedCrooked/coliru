#include <iostream>
#include <string>
#include <cctype>

int main()
{
    double number, second_number ;
    std::string operation ;

    //std::cout << "Please enter an expression (like `4 * 5` or `ln 5`): ";

    // skip over leading white-space
    char c ;
    std::cin >> c ; // read the first non-whitespace character
    std::cin.putback(c) ; // and put it back

    // look at the first non-whitespace character
    if( std::isdigit(c) ) // if the first char is a digit
    {
        // input is of the form 'number operator number';
        // read it into number, operation, second_number
        std::cin >> number >> operation >> second_number ;

        std::cout << "number==" << number << " operation=='" << operation
                   << "' second_number==" << second_number << '\n' ;
    }

    else if( std::isalpha(c) ) // if the input starts with an alphabet
    {
        // input is of the form 'operator number';
        // read it into operation, number
        std::cin >> operation >> number ;

        std::cout << "operation=='" << operation << "' number==" << number << '\n' ;
    }
    
    // else // error in input: first non-whitespace character is neither a digit nor a letter
}
