#include <iostream>
#include <boost/regex.hpp>

bool validate_uuid(const std::string& s)
{
   static const boost::regex e("[a-f0-9]{8}-[a-f0-9]{4}-4[a-f0-9]{3}-[89aAbB][a-f0-9]{3}-[a-f0-9]{12}");
   return regex_match(s, e);
}

int main()
{
   std::cout<< std::boolalpha 
        << validate_uuid("00000000-0000-0000-0000-00000000000K") << std::endl
        << validate_uuid("00000000-0000-4000-0000-000000a0000f") << std::endl
        << validate_uuid("00000000-0000-4000-8000-000000a00000") << std::endl;
    
    return 0;
}
