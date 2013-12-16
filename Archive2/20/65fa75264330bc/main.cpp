#include <iostream>
#include <string>
#include <vector>

int main()
{
    int myFavNum = 7;
    std::string myName = "Tyler";
    
    auto fn = [myName&]{
        return myName;
    };
    
    myName = "Colby";
    
    cout << fn();
    return 0;
}
