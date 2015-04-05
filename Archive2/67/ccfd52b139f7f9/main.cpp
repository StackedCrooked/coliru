/*Substituablity: Base class pointer can be assigned with either base class object or derived class object
-> we can achieve this by overriding.( this can be achieved using virtual function)
-> Compiler creates one virtual table(if you make a function virtual ? )
*/

#include<iostream>
class a{
public:
    virtual void m1()
    {
        std::cout << "m1 of A" <<std::endl;
    }
};
class b: public a
{
public:
    void m1()
    {
        std::cout<<"m1 of b" << std::endl;
    }
};
int main()
{
    a *A;
    b B;
    A = &B;
    A->m1();  // always points to M1() of b
}
