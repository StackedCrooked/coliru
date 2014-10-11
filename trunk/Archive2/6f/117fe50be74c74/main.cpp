#include <iostream>

int main()
{
   int integer_4 = 4 ;
   int character_literal_4 = '4' ;

   std::cout << "integer_4 == " << integer_4 << "\n\n"
             << "character_literal_4 == " << character_literal_4 << "\n\n"
             << "integer_4 + '0' == " << integer_4 + '0' << "\n\n"
             << "character_literal_4 - '0' == " << character_literal_4 - '0' << "\n\n" ;
}
