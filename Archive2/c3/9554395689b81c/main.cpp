

#include <iostream>

class cu{
public :
    cu(bool in){
        std::cout << "boo";
    }
    
    cu(const char*) = delete;
};

int main()
{
    cu cu("hello");

}