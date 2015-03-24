#include <iostream>
 
struct A
{
    int i;
 
    A ( int i ) : i ( i ) {}
 
    ~A()
    {
        std::cout << "~a" << i << std::endl;
    }
};
 
int main()
{
    A a1(1);
    A* p;
 
    { // nested scope
        A a2(2);
        p = new A(3);
    } // a2 out of scope
 
    delete p; // calls the destructor of a3
}