#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> myVector = { "y", "e", "?" };
bool myBool = true;

void myFunction(){
    for(unsigned i = 0; i < myVector.size(); ++i) {
        myVector[i] = "foo";
    }
    if(myBool) {
        std::cout << "bar" << std::endl;
    }
    return;
}

int main() {
    myFunction();
}