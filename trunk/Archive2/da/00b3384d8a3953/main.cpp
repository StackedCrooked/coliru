#include <iostream>
#include <string>
#include <vector>

struct myType{
    int a; 
    int b; 
    int c;
};

std::vector<myType> myVector(100);
bool myBool = true;

void myFunction(){
    for(unsigned i = 0; i < myVector.size(); ++i) {
        myVector[i].a = 5;
    }
    if(myBool) {
        std::cout << "bar" << std::endl;
    }
    return;
}

int main() {
    myFunction();
}