#include<iostream>

class A
{
    public :

    A() {
        cout<<"\nin A const";
    }

    ~A() {
        cout<<"\nin A dest";
    }
};


int main()
{
    A a;
    a.~A();
}