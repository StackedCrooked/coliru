#include <sstream>
#include <iostream>
 
int main()
{
    { 
    std::istringstream s1("Hello, world.");
    char str[6];
    s1.get(str, sizeof str, ',');  // read up to the comma; leaves comma on the stream
    std::cout << "after reading \"" << s1.str() << "\" up to comma using istream::get,\n"
              << "the array contains \"" << str << "\"\n"
              << "next character to read is '" <<  (char)s1.get() << "'\n";
    }
                 
    { 
    std::istringstream s1("Hello, world.");
    char str[6];
    s1.getline(str, sizeof str, ',');  // read up to the comma; leaves comma on the stream
    std::cout << "after reading \"" << s1.str() << "\" up to comma using istream::getline,\n"
              << "the array contains \"" << str << "\"\n"
              << "next character to read is '" <<  (char)s1.get() << "'\n";
    }
}
