#include <iostream>
#include <sstream>

int main()
{
    std::string value = "foo";
    std::stringstream ss("");

    if (ss >> value) // this will fail
        std::cout << "value read successfully: " << value << std::endl;
        
    // will value still be guaranteed to be zero?
    std::cout << "value is " << value << std::endl;
}