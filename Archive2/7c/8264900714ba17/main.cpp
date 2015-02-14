#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct A
{
    A()
    {
        cout<<"CA"<<endl;       
    }
    
    virtual ~A()
    {
        cout<<"DA"<<endl;   
    }
    
    virtual void writeOut()
    {
        cout<<"WA"<<endl;   
    }
};

struct B : public A
{
    B()
    {
        cout<<"CB"<<endl;       
    }
    
    virtual ~B()
    {
        cout<<"DB"<<endl;   
    }
    
    virtual void writeOut()
    {
        cout<<"WB"<<endl;   
    }
};

int add(int lhs,int rhs)
{
    return lhs + rhs;    
}


int main()
{
    
    cout<<add(100,18)<<endl;
    A* object = new B();
    object->writeOut();
    delete object;
    return 0;
}
