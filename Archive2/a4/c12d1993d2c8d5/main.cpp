#include<iostream>
using namespace std;

class base
{
public:
void fun()
{
cout<<"Base class";
}
};

class der : public base
{
public:
    void fun()
    {
     cout<<"Derived class";
    }
};

int main()
{
 base* pb;

 der d1;
 pb=&d1;             
 pb->fun();        

 static_cast<der*>(pb)->fun();   


 return 0;
}