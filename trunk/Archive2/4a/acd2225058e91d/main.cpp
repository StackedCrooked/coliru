#include <string>

struct X{
    std::string s;
};

struct Y{
    X x;
    
    Y(std::string s) : x{s}{}
};

int main(){}