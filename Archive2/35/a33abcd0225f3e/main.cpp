#include <iostream>
#include <string>

int char_to_int( char c ) // convert char to int ( '7' to 7 etc. )
{
    // '1' - '0' == 1,    '4' - '0' == 4,   '8' - '0' == 8 etc.
    if( std::isdigit(c) ) return c - '0' ;
    else return 10 ; // error, invalid
}

int check_digit( std::string str )
{
    int sum = 0 ;

    // sum up the numeric value of all the digits
    for( unsigned int i = 0 ; i < str.size() ; ++i ) sum += char_to_int( str[i] ) ;

    const int remainder = sum%10 ; // remainder when divided by 10

    if( remainder == 0 ) return 0 ; // already a multiple of 10
    else return 10 - remainder ; // closest number to this sum that creates a multiple of 10.
}

const std::string invalid = "Invalid" ; //

std::string barCode( char digit )
{
    // we can use a lookup table to get the bar code
    static const std::string codes[] =
    {
      "||:::", // 0
      ":::||", // 1
      "::|:|", // 2
      "::||:", // 3
      ":|::|", // 4
      ":|:|:", // 5
      ":||::", // 6
      "|:::|", // 7
      "|::|:", // 8
      "|:|::", // 9
      invalid // invalid
    };

    // convert char digit to its int value, and lookup in the table
    return codes[ char_to_int(digit) ] ;
}

int main()
{
    std::string zipCode;
    std::string result;

    std::cout << "Please enter a zip code: ";
    std::cin >> zipCode;

    for ( unsigned int i = 0; i < zipCode.length(); i++ )
    {
        const std::string currentBarcode = barCode ( zipCode[i] );

        if ( /*currentBarcode.compare ("Invalid") == 0*/ currentBarcode == invalid )
        {
            std::cout << "You have entered a number that is not valid\n" ; // << endl;
            break;
        }

        result += currentBarcode ;
    }

    // add check digit as the last digit
    char last_digit = check_digit(zipCode) + '0' ; // convert to a char: 3 + '0' == '3' etc
    result = result + barCode(last_digit);

    std::cout << "|" << result << "|\n";
}
