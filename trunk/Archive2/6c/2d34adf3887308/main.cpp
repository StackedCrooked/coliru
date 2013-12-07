#include <iostream>
#include <string>
#include <vector>

int main()
{
    int myFavNum = 7;
    std::string myName = "Tyler";
    
    //Capture "Tyler" and his fav number
    auto fn = [myFavNum, myName]
    {
        std::cout << myName << "'s favorite number is " << myFavNum << std::endl;
    };
    
    myName = "Colby";
    myFavNum = 13;
    
    //Displays the captured values
    fn();
    
    //Want to capture again, this time capture "Colby" and his fav number
    fn = [myFavNum, myName];
    
    fn();
    return 0;
}
