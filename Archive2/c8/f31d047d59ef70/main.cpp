#include <string>
#include <iostream>
#include <future>

void asv(std::string s){
    std::cout << "asv" << std::endl;
    std::cout << s << std::endl;
}

int main(){
    
    std::string s("test");
    std::async(std::launch::async, asv, std::move(s));
    
    return 0;
}