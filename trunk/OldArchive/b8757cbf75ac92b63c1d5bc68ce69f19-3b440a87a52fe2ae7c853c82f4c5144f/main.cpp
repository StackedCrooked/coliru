#include <iostream>
#include <string>

using namespace std;

struct detective
{
    void foo() & {std::cout << "lvalue" << std::endl;}
    void foo() && {std::cout << "rvalue" << std::endl;}
};

int main(){
 
    detective d;
    d.foo();
    detective().foo();
    return 0;
}