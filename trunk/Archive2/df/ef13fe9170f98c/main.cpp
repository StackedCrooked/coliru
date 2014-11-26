#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct str
{
    ~str()
    {
        cout << "str::~str()" << endl;
    } 
};

str && Funcf(str arg)
{
    return (str&&)arg;
}

int main()
{
    
    std::cout << "Current Expression_0" << endl << (Funcf(str()), "Current Expression, comma operator") << endl << "Current Expression_1" << std::endl;
}
