#include <iostream>
#include <string>
#include <sstream>

struct name_value_pair { std::string name; int value; };

// convert object of type name_value_pair into a sequence of characters
std::string to_string( name_value_pair nvpair )
{
    // step 1. create an output stringstream
    std::ostringstream stm;

    // step 2. write things into the stream
    stm << "{ name: '" << nvpair.name << "', value: " << nvpair.value << " }";

    // step 3. get a copy of the underlying string and return it.
    return stm.str();
}

int main()
{
    name_value_pair pcount = { "post count", 59 };
    const std::string str = to_string(pcount);
    std::cout << "str contains: " << str << '\n';
}
