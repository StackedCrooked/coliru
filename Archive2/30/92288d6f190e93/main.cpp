/* Deleting a derived class object using a pointer to a base class 
that has a non-virtual destructor results in undefined behavior. 
To correct this situation, the base class should be defined with a virtual destructor.
*/

#include<iostream>
class base
{
    public:
    base()
    {
        std::cout << "constructing base " << std::endl;
    }
    virtual ~base()
    {
        std::cout << "Destructor base " << std::endl;
    }
};
class derived : public base
{
    public:
    derived()
    {
        std::cout << "constructing derived " << std::endl;
    }
    ~derived()
    {
        std::cout << "destructing derived " << std::endl;
    }
};

int main()
{
    derived *dp = new derived;
    base *bp ;
    bp = dp;
    
    delete bp;
}



