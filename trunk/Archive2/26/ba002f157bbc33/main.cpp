#include <iostream>
#include <string>
#include <sstream>

int main()
{
    const std::string text =
         "lastname_a, firstname_a, partnumber_a, date_a\n"
         "lastname_b, firstname_b, partnumber_b, date_b\n"
         "lastname_c, firstname_c, partnumber_c, date_c\n"
         "lastname_d, firstname_d, partnumber_d, date_d\n" ;

    {
        std::istringstream file(text) ;
        std::string field1, field2, field3, field4 ;
        while( std::getline( file, field1, ',' ) &&
               std::getline( file, field2, ',' ) &&
               std::getline( file, field3, ',' ) &&
               std::getline( file, field4 ) )
        {
            std::cout << "1. " << field1 << "  2. " << field2
                       << "  3. " << field3 << "  4. " << field4 << '\n' ;
        }
    }

    std::cout << "--------------------------------------------------\n" ;

    {
        std::istringstream file(text) ;
        std::string line ;
        while( std::getline( file, line ) )
        {
            std::string field ;
            std::istringstream sstm(line) ;
            int n = 0 ;
            while( std::getline( sstm, field, ',' ) )
                std::cout << ++n << ". " << field << "  " ;
            std::cout << '\n' ;
        }
    }
}