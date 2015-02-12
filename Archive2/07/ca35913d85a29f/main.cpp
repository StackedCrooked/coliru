// Example program
#include <iostream>
#include <sstream>
#include <string>

int main()
{
    std::string myLine{"Box_01: 1 2 3"};
    
    std::stringstream ss(myLine);
    std::getline(ss, myLine, ':');
    
    for(std::string attribute; std::getline(ss, attribute, ' '); )
    {
        if(attribute.empty())
            continue;
            
        int myDimension = std::stoi(attribute);
        //do stuff with it
        
        std::cout << myDimension << std::endl;
    }
}
