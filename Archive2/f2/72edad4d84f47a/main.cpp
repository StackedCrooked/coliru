#include <iostream>
#include <string>
#include <sstream>

struct name_value_pair { std::string name; int value; };

// convert object of type name_value_pair into a sequence of characters
std::string to_string( name_value_pair nvpair )
{
    // step 1. create an output stringstream
    std::ostringstream stm;

    // step 2. write name and value into the stream
    stm << "{ name: '" << nvpair.name << "', value: " << nvpair.value << " }";

    // step 3. get a copy of the underlying string; and return it.
    return stm.str();
}

// convert string back to object of type name_value_pair
name_value_pair to_nvpair( std::string str )
{
    // step 1. crate a name_value_pair object
    name_value_pair nvpair  = { "anonymous", 0 };
    
    // step 2. create an input stringstream to read from the given string
    std::istringstream stm(str);

    // step 2. read the information in the string
    std::string temp ;
    std::getline( stm, temp, '\'' ); // 2a. discard everuthing upto the first '
    std::getline( stm, nvpair.name, '\'' ); // 2b. read the name
    std::getline( stm, temp, ':' ); // 2c. discard everuthing upto the next :
    stm >> nvpair.value; // 2d. read the value
    
    // step 3. return the object.
    return nvpair ;
}

int main()
{
    name_value_pair pcount = { "post count", 59 };
    const std::string str = to_string(pcount);
    std::cout << "str contains: " << str << '\n';
    
    name_value_pair pcount2 = to_nvpair(str) ;
    std::cout << pcount2.name << " => " << pcount2.value << '\n' ;
    
}
