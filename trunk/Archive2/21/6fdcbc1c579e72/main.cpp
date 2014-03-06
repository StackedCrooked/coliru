#include <iostream>
#include <vector>
#include <string>
#include <algorithm>


struct Buffer
{
    std::string donnees_;
    
    Buffer(std::string& donnees)
        : donnees_(donnees) {
    }
    
    Buffer(std::string&& donnees)
        : donnees_(std::move(donnees)) {
    }
};


int main()
{
    std::string s = "bonjour";
    
    Buffer b1(s);
    Buffer b2(s);
    Buffer b3(std::string("bonjour"));
    
    std::cout << s << std::endl;
    std::cout << b1.donnees_ << std::endl;
    std::cout << b2.donnees_ << std::endl;
    std::cout << b3.donnees_ << std::endl;
}
