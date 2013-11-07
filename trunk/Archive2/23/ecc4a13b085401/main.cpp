#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::istringstream file
    (
         "1957-02-21 43.48\n"
         "1957-02-22 . \n"
         "1957-02-25 43.38\n"
         "1957-02-26 43.45"
    );


    std::string line ;
    while( std::getline( file, line ) ) // for each line in file
    {
        std::istringstream stm(line) ; // make an input stringstream

        std::string date ;
        double value ;
        if( stm >> date >> value ) // if we could read a date and a value
        {
            std::cout << "date: " << date << "  value: " << value << '\n' ;
            // use date and value
        }
        else // attempt to read failed
        {
            std::cout << "imcomplete data discarded: " << line << '\n' ;
            // discard the line
        }
    }
}
