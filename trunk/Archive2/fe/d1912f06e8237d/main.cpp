#include <iostream>
#include <string>

struct File { 
    std::string f;
    File(std::string f) : f(f) {}
};

int main(int argc, const char* argv[]){
    File f1((std::string("")));
    std::cout << f1.f;
}