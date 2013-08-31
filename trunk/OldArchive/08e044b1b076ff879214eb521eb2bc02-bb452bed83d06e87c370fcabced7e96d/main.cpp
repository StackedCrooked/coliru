#include <string>
#include <iostream>

int main()
{
    std::string testString = "PFAIL";
    std::string response = "PFAIL\n";
    
    if( response.find(testString) != std::string::npos )
    {
        std::cout << "do something" << std::endl;
    }
}
