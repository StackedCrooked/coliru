#include <iostream>
#include <string>

struct File { 
    std::string f;
    File(std::string f) : f(f) {}
};

int main(int argc, const char* argv[]){
    std::string x = "";
    File f1(x);
    std::cout << f1.f;
}