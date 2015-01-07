#include <iostream>   


class Abc
{
  public:
    Abc() { std::cout << "construct " << this << std::endl; }
    ~Abc() { std::cout << "destruct " << this << std::endl; }
    Abc(Abc const & other)
        : a(other.a), b(other.b), c(other.c)
    { std::cout << "construct " << this << " by copy from " << &other << std::endl; }
    
    Abc & operator=(Abc const & other)
    {
        a = other.a;
        b = other.b;
        c = other.c;
        
        std::cout << "assign " << this << " by copy from " << &other << std::endl;
        
        return *this;
    }
    
    int a;
    int b;
    int c;
};

Abc fun1()
{
    Abc obj;
    obj.a = 3;
    obj.b = 4;
    obj.c = 5;
    return obj;

}

int main ()
{
     Abc obj1 = fun1();
     std::cout<<"obj1 address is "<<&obj1<<std::endl;

     const Abc &obj11 = fun1();
     std::cout<<"obj11 address is "<<&obj11<<std::endl;



    return 0;

}