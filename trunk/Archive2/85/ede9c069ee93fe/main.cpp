#include <exception>

void foo()
try
{
    std::exception e;
    throw e; 
}
catch (std::exception ex) 
{
}

int main(){ foo(); }