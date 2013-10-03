#include <iostream>
#include <sstream>
#include <string>

int main()
{
    const std::string inputString {"This is Derek's Test String!"};
    
    std::string tokenString;
    
    std::istringstream inputStringStream(inputString);
    
    while (inputStringStream >> tokenString)
    {
        std::cout << tokenString << std::endl;   
    }
    
    const std::string secondString {"This,is,the,second,string"};
    
    std::istringstream secondStringStream(secondString);
    
    while (std::getline(secondStringStream, tokenString, ','))
    {
        std::cout << tokenString << std::endl;   
    }
    
    return 0;
}
