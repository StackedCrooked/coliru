#include <iostream>
#include <string>
#include <vector>
#include <functional>

std::function<void(std::string,int)> getFunction(std::string na, int num){
    return [na,num]{ std::cout << na << " " << num << std::endl; };
}

int main(){
    std::string myName = "Tyler";
    int myNum = 7;
    function<void()> fn = getFunction(myName,myNum);
    //prints tyler and 7
    fn();
    myName = "Colby";
    myNum = 13;
    //still prints tyler and 7
    fn();
    fn = getFunction(myName,myNum);
    //new value was captured, now displays colby and 13
    fn();
    return 0;
}
