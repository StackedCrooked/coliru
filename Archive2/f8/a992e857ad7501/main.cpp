#include <iostream>
#include <string>

int main() {
    std::string a = "Hey";
    std::string *b = new std::string("Hey");
    
    // comparing pointers (will not be equal)
    if(&a == b) std::cout <<"1"<<std::endl;
    
    // comparing values
    if(a == *b) std::cout <<"2"<<std::endl;
    
    
    // cleanup
    delete b;
}