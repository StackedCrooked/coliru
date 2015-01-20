#include <exception>

void foo()
try
{ 
    throw std::exception(); 
}
catch (std::exception ex) 
{
}

int main(){ foo(); }