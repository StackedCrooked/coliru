#include <iostream>
struct A
{

   virtual void step() = 0;
   
   void bla(){ step();};
};

template <typename T>
struct B : public A
{
    virtual void step()
    {
        T t;
        std::cout << t.print();
    }
};
    
struct msg
{
    std::string print() { return "something";}
};
int main()
{

     B<msg> b;
     b.bla();
}
