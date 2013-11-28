#include <string>
#include <iostream>

bool has_special_chars( const std::string& s)
{
   return s.find_first_of("~`!@#$%^&*()_+-=\\/\?><,.") != std::string::npos;
}

int main()
{
   const std::string s = "This is a password";
   std::cout<<has_special_chars("Test1")<<std::endl;
   std::cout<<has_special_chars("Test1ASD!As")<<std::endl;
   return 0;  
}