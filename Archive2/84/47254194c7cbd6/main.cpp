#include <iostream>
#include <exception>

void foo()
try
{ 
    std::exception e();
    throw e; 
}
catch (std::exception ex) 
{
    //extern int e;
}
int main(){ foo(); }