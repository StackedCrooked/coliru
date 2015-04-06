#include<iostream>

class base
{
public:
    base(){}
    virtual ~base(){}
    virtual void show()
    {
        std::cout << "In base Class"<<std::endl;
    }
};
class derived:public base
{
    void show()
    {
        std::cout << "In derived Class"<<std::endl;
    }
};
int main()
{
    base *bp = new derived();
    derived *dp=NULL;
    
    // To find whether basePointer is pointing to Derived type of object
    dp = dynamic_cast <derived*>(bp);
    
    if(dp!=NULL)
        std::cout << "Base pointer is pointing to a derived object" << std::endl;
    
    // Requires virtual destructor 
    delete bp;
    bp = NULL;
}
