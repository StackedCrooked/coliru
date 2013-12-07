#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string myName = "Tyler";
    
    auto fn = [&myName]{
        return myName;
    };
    
    myName = "Colby";
    
    return 0;
}

int age(std::string x){
    if(x == "Colby"){
        cout << 19;
    }else{
        cout << 18;
    }
}
