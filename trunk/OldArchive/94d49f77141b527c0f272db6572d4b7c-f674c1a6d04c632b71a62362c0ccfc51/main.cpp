#include <stdexcept>
#include <iostream>


int
main ()
try
{
    
    bool flag = false;
    try
    {
        throw 1;
    }
    catch (...)
    {
        flag = true;
    }
    
    if (flag)
        throw;
    
    return 0;
}
catch (...)
{
    std::cout << "caught excepton";
    return 1;
}
