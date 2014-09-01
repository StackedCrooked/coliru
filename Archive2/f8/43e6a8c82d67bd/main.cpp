#include <iostream>
#include <typeinfo>

using std::cout;
using std::endl;

struct A
{
    ~A()
    {
        cout << "~A" << endl; //side-effect
    }
    
    A()
    { 
        cout << "A()" << endl;
    }
};

A *a = new A;


int main()
{
    //Prints A()
    //Is such behavior undefined?
}