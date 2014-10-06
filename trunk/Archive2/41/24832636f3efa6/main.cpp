#include <iostream>
 
int main()
{

    struct myobj
    {
        myobj(int ii) : i(ii) {} 
        int i;
    };
    
    myobj * p = new myobj(2);
    std::cout << " The number i is : " << p->i << std::endl;
    
    p = 0;
    try 
    {
        std::cout << " The number i is : " << p->i << std::endl;
    }
    catch(...)
    {
        std::cout << "caught everything ";
    }
    
}