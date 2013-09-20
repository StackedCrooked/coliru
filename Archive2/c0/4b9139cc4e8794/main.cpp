#include<iostream>

class A
{
    public :

    A() {
        std::cout<<"\nin A const";
    }

    ~A() {
        std::cout<<"\nin A dest";
    }
};


int main()
{
    A a;
    a.~A();
}